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

	private:
		Parameters parameters{ *this };

		BypassTransitionSmoother bypassTransitionSmoother;

		Tremolo tremolo;

		juce::AudioPlayHead::PositionInfo currentPosInfo;
		juce::AudioPlayHead* playhead;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
	};
}  // namespace sky_trem
