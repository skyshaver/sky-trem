
namespace sky_trem {

	Tremolo::Tremolo() {		
		for (auto& lfo : lfos) {
			lfo.setFrequency(5.f, true); // force prevents smoothing
		}
	}

	void Tremolo::prepare(double sampleRate, int expectedMaxFramesPerBlock) {
		const juce::dsp::ProcessSpec pspec{ .sampleRate = sampleRate,
										   .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
										   .numChannels = 1u };
		for (auto& lfo : lfos) {
			lfo.prepare(pspec);
		}

		lfoSmoothed.reset(sampleRate, 0.1);
		gainSmoothed.reset(sampleRate, 0.01);
	}

	void Tremolo::process(juce::AudioBuffer<float>& buffer) noexcept {

		updateModulationDepth();
		updateLfoWaveform();
		updateGain();

		// for each frame
		for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {			
			
			const auto lfoValue = getNextLfoValue();
			const auto modValue = (1.f - currentModulationDepth) + currentModulationDepth * (0.5f * (lfoValue + 1.f));  // may be a better implementation
			// const auto modValue = (currentModulationDepth * lfoValue + 1.f); // uncomment this for testing just the raw waveform shape

			// for each channel sample in the frame
			for (const auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {

				const auto inputSample = buffer.getSample(channelIndex, frameIndex);

				const auto outputSample = inputSample * modValue * getNextGainValue();

				buffer.setSample(channelIndex, frameIndex, outputSample);
			}
		}
	}

	void Tremolo::setModulationRate(float modRate) {
		for (auto& lfo : lfos) {
			lfo.setFrequency(modRate);
		}
	}

	void Tremolo::setModulationDepth(float modDepth) {
		currentModulationDepth = modDepth;
	}

	void Tremolo::updateModulationDepth() {
		if (currentModulationDepth != modulationDepthToSet) {
			modulationDepthSmoothed.setCurrentAndTargetValue(getNextModulationDepthValue());
			currentModulationDepth = modulationDepthToSet;
			modulationDepthSmoothed.setTargetValue(getNextModulationDepthValue());
		}
	}

	void Tremolo::setLfoWaveform(LfoWaveform lwf) {
		// no clean way to check that lwf is a valid member of LfoWaverform without listing all possible values again
		// which makes me think this should be an associative container, then you can check it's a member before assigning or maybe a vector of "Lfoclass" or something
		lfoToSet = lwf;
	}

	float Tremolo::getNextLfoValue() {
		if (lfoSmoothed.isSmoothing()) {
			return lfoSmoothed.getNextValue();
		}
		return lfos[std::to_underlying(currentLfo)].processSample(0.f); // pass 0 to just get the generated value
	}

	void Tremolo::updateLfoWaveform() {
		if (currentLfo != lfoToSet) {
			lfoSmoothed.setCurrentAndTargetValue(getNextLfoValue());
			currentLfo = lfoToSet;
			lfoSmoothed.setTargetValue(getNextLfoValue());
		}
	}

	void Tremolo::setGainInDB(float gainInDb) {
		// normalizedGain = std::pow(10.f, gainInDb / 20.f);
		gainToSet = juce::Decibels::decibelsToGain(gainInDb);
		// DBG(normalizedGain);
	}

	float Tremolo::getNextGainValue() {
		if (gainSmoothed.isSmoothing()) {
			return gainSmoothed.getNextValue();
		}
		return currentGain;
	}

	float Tremolo::getNextModulationDepthValue() {
		if (modulationDepthSmoothed.isSmoothing()) {
			return modulationDepthSmoothed.getNextValue();
		}
		return currentModulationDepth;
	}

	void Tremolo::updateGain() {
		if (currentGain != gainToSet) {
			gainSmoothed.setCurrentAndTargetValue(getNextGainValue());
			currentGain = gainToSet;
			gainSmoothed.setTargetValue(getNextGainValue());
		}
	}

	void Tremolo::reset() noexcept {
		for (auto& lfo : lfos) {
			lfo.reset();
		}

	}
}  // namespace sky_trem



/*
The implementation of the tremolo effect here is textbook correct, although it should be noted that this is generally not the best implementation when directly processing audio signals.
In it’s current form, the modulation will produce multipliers above 1.0 (shown at 2:23), which will boost the amplitude of the audio signal which can cause clipping if the volume of the input signal is already quite loud.

A better implementation is:

output = (1.0 - modulationDepth) + modulationDepth * (0.5 * (lfoValue + 1.0))

This will keep the modulation values between 0 and 1, and will apply the tremolo from the top down,
meaning that we only modulate between the original amplitude of the audio signal, and a decreased amount of amplitude, specified by the modulationDepth.
At 100% modulation depth, the original implementation would output a signal that varies between completely silent and twice as loud as the input signal.
With the modified implementation, the signal will vary between silence and the original volume of the signal, so there is no chance of clipping.
*/