#pragma once

namespace sky_trem {
	class PluginProcessor : public juce::AudioProcessor {

	public:
		PluginProcessor();

		void prepareToPlay(double sampleRate, int expectedMaxFramesPerBlock) override;

		void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
		using AudioProcessor::processBlock;

		void releaseResources() override;

		juce::AudioProcessorEditor* createEditor() override;
		bool hasEditor() const override;

		const juce::String getName() const override;

		bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

		bool acceptsMidi() const override;
		bool producesMidi() const override;
		bool isMidiEffect() const override;
		double getTailLengthSeconds() const override;

		int getNumPrograms() override;
		int getCurrentProgram() override;
		void setCurrentProgram(int index) override;
		const juce::String getProgramName(int index) override;
		void changeProgramName(int index, const juce::String& newName) override;

		void getStateInformation(juce::MemoryBlock& destData) override;
		void setStateInformation(const void* data, int sizeInBytes) override;

		juce::AudioProcessorParameter* getBypassParameter() const override;

		Parameters& getParameterRefs() noexcept { return parameters; }

		bool getAndResetIsQuarterNote() {
			if (isQuarterNote.value)
				return isQuarterNote.exchange(!isQuarterNote.value);
			else
				return isQuarterNote.value;
		}

	private:
		Parameters parameters{ *this };

		BypassTransitionSmoother bypassTransitionSmoother;

		Tremolo tremolo;

		juce::AudioPlayHead* playhead;
		juce::AudioPlayHead::PositionInfo currentPosInfo;
		float currentBpm{ 120.f };
		float currentBpmDivsion;
		double currentSampleRate;
		juce::AudioPlayHead::TimeSignature currentTimeSignature;
		int64_t samplesPerNumerator;
		int64_t samplesPerBar;

		juce::Atomic<bool> isQuarterNote{ false };		
			
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
	};
}  // namespace sky_trem
