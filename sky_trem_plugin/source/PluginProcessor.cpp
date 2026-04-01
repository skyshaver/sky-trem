
namespace sky_trem {

	PluginProcessor::PluginProcessor()
		: AudioProcessor(BusesProperties()
			.withInput("Input", juce::AudioChannelSet::stereo(), true)
			.withOutput("Output", juce::AudioChannelSet::stereo(), true)) {
	}

	const juce::String PluginProcessor::getName() const {
		return PLUGIN_NAME;
	}

	bool PluginProcessor::acceptsMidi() const {
		return false;
	}

	bool PluginProcessor::producesMidi() const {
		return false;
	}

	bool PluginProcessor::isMidiEffect() const {
		return false;
	}

	double PluginProcessor::getTailLengthSeconds() const {
		return 0.0;
	}

	int PluginProcessor::getNumPrograms() {
		// Some hosts don't cope very well if you tell them there are 0 programs, so
		// this should be at least 1, even if you're not really implementing programs.
		return 1;
	}

	int PluginProcessor::getCurrentProgram() {
		return 0;
	}

	void PluginProcessor::setCurrentProgram(int index) {
		juce::ignoreUnused(index);
	}

	const juce::String PluginProcessor::getProgramName(int index) {
		juce::ignoreUnused(index);
		return {};
	}

	void PluginProcessor::changeProgramName(int index, const juce::String& newName) {
		juce::ignoreUnused(index, newName);
	}

	void PluginProcessor::prepareToPlay(double sampleRate, int expectedMaxFramesPerBlock) {
		// Use this method as the place to do any pre-playback
		// initialization that you need, e.g., allocate memory.		
		
		currentSampleRate = sampleRate;
		currentBpmDivision = noteDivToBpmDiv[parameters.bpmDivision.getCurrentChoiceName()];	
		
		tremolo.prepare(sampleRate, expectedMaxFramesPerBlock);
		bypassTransitionSmoother.prepare({
			.sampleRate = sampleRate,
			.maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
			.numChannels = static_cast<juce::uint32>(juce::jmax(getTotalNumInputChannels(), getTotalNumInputChannels()))
			});
	}

	void PluginProcessor::releaseResources() {		
		tremolo.reset();
		bypassTransitionSmoother.reset();
	}

	bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
		// This is the place where you check if the layout is supported.
		// In this template code we only support mono or stereo.
		// Some plugin hosts, such as certain GarageBand versions, will only
		// load plugins that support stereo bus layouts.
		if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
			layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
			return false;
		}

		// This checks if the input layout matches the output layout
		if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) {
			return false;
		}

		return true;
	}

	void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
		juce::ignoreUnused(midiMessages);

		juce::ScopedNoDenormals noDenormals;
		const auto totalNumInputChannels = getTotalNumInputChannels();
		const auto totalNumOutputChannels = getTotalNumOutputChannels();

		// In case we have more outputs than inputs, this code clears any output
		// channels that didn't contain input data, (because these aren't
		// guaranteed to be empty - they may contain garbage).
		// This is here to avoid people getting screaming feedback
		// when they first compile a plugin, but obviously you don't need to keep
		// this code if your algorithm always overwrites all the output channels.
		for (const auto channelToClear : std::views::iota(totalNumInputChannels, totalNumOutputChannels)) {
			buffer.clear(channelToClear, 0, buffer.getNumSamples());
		}

		// get bpm info and set tis stuff
		playhead = this->getPlayHead();
		currentPosInfo = *playhead->getPosition();

		if (currentPosInfo.getBpm()) {
			currentBpm = static_cast<float>(*currentPosInfo.getBpm());
		}
		else {
			// we're in standalone for testing so set to dummy bpm
			currentBpm = 120.f;
		}

		// also factor out samplesPerNumerator and just use samplesPerBar and a LUT?
		auto bps = 60.0 / currentBpm;
		samplesPerNumerator = juce::roundToInt(currentSampleRate * bps); // assume 1/4 note for now
		samplesPerBar = juce::roundToInt(samplesPerNumerator * currentTimeSignature.denominator); // this could get tricky with like 6/8 etc?

		if (currentPosInfo.getTimeSignature()) {
			if (*currentPosInfo.getTimeSignature() != currentTimeSignature) {
				currentTimeSignature = *currentPosInfo.getTimeSignature();
				// update bar length if time sig changes?
				samplesPerBar = juce::roundToInt(samplesPerNumerator * currentTimeSignature.denominator);

			}

		}
		// can we factor out currentBpm and just hold parameters.bpm?
		parameters.bpm = currentBpm;
		currentBpmDivision = noteDivToBpmDiv[parameters.bpmDivision.getCurrentChoiceName()];

		if (!parameters.isModDepthRando.get()) {
			tremolo.setModulationDepth(parameters.modulationDepth.get());
		}

		if (parameters.isRateInHz.get()) {						
			tremolo.setModulationRate(parameters.modulationRate.get());						
		} 
		else {
			
			// should we wait till the next beat subdivision to set the mod rate?
			tremolo.setModulationRate(parameters.bpm / currentBpmDivision);

			if (currentPosInfo.getIsPlaying() && currentPosInfo.getTimeInSamples()) {
				auto tis = *currentPosInfo.getTimeInSamples();	
				for (auto i = 0; i < buffer.getNumSamples(); i++) {
					
					if ((tis + i) % samplesPerNumerator == 0) { 						
						// TODO: setting an atomic in hot loop, not ideal, should set local bool and update atomic at end of processblock?
						isQuarterNote.set(true);
					}

					if ((tis + i) % (samplesPerBar / noteDivToSpbDiv[parameters.bpmDivision.getCurrentChoiceName()]) == 0) {
						// float between 1.01f and 1.03f
						auto nextRand = 1.f + (juce::Random::getSystemRandom().nextInt(juce::Range<int>(1000, 3000)) * 0.00001f);						
						tremolo.setModulationDepth(parameters.modulationDepth.get() * nextRand);
					}

					if ((tis + i) % samplesPerBar == 0) {						
						// try resetting lfos every bar
						tremolo.reset();
					}
				}								
			}
		}

		
		tremolo.setGainInDB(parameters.gainInDb.get());
		tremolo.setLfoWaveform(static_cast<Tremolo::LfoWaveform>(parameters.lfoWaveform.getIndex()));

		bypassTransitionSmoother.setBypass(parameters.bypass.get());

		// you may need to check for a delay if your process introduces delay
		if (parameters.bypass.get() && !bypassTransitionSmoother.isTransitioning())
			return;		

		bypassTransitionSmoother.setDryBuffer(buffer);

		tremolo.process(buffer);

		bypassTransitionSmoother.mixToWetBuffer(buffer);

		
	}

	bool PluginProcessor::hasEditor() const {
		return true;
	}
	
	juce::AudioProcessorEditor* PluginProcessor::createEditor() {
		return new PluginEditor(*this);
	}

	void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
		juce::MemoryOutputStream outputStream{ destData, true };
		JsonSerializer::serialize(parameters, outputStream);
	}

	void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
		
		juce::MemoryInputStream inputStream{ data, static_cast<size_t>(sizeInBytes), false };		
		const auto result = JsonSerializer::deserialize(inputStream, parameters);
		if (result.failed()) {
			DBG("setStateInformation: " << result.getErrorMessage());
		}
		bypassTransitionSmoother.setBypassForced(parameters.bypass.get());
	}

	juce::AudioProcessorParameter* sky_trem::PluginProcessor::getBypassParameter() const {
		return &parameters.bypass;
	}

}  // namespace sky_trem

// This creates new instances of the plugin.
// This function definition must be in the global namespace.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
	return new sky_trem::PluginProcessor();
}
