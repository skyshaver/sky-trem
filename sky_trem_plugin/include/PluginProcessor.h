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
		float currentBpmDivision;
		double currentSampleRate;
		juce::AudioPlayHead::TimeSignature currentTimeSignature;
		int64_t samplesPerNumerator;
		int64_t samplesPerBar;

		std::map<juce::String, float> noteDivToBpmDiv {
			{ "1/32", 7.5f },
			{ ".1/32", 11.2465f },
			{ "1/16", 15.f },
			{ ".1/16", 22.5141f },
			{ "1/8", 30.f },
			{ ".1/8", 44.9438f },
			{ "1/4", 60.f },
			{ ".1/4", 90.2256f },
			{ "1/2", 120.f },
			{ ".1/2", 179.1045f },
			{ "1/1", 240.f }
		};

		// for simplicity use whole numbers, need floats for accuracy of . 
		std::map<juce::String, int64_t> noteDivToSpbDiv {
			{ "1/32", 32 },
			{ ".1/32", 32 },
			{ "1/16", 16 },
			{ ".1/16", 16 },
			{ "1/8", 8 },
			{ ".1/8", 8 },
			{ "1/4", 4 },
			{ ".1/4", 4 },
			{ "1/2", 2 },
			{ ".1/2", 2 },
			{ "1/1", 1 }
		};

		std::map<juce::String, juce::Range<int>> randoRangeToIntRange {
			{ "3%", juce::Range<int>{1000, 3000} },
			{ "5%", juce::Range<int>{1000, 5000} },
			{ "10%", juce::Range<int>{1000, 10000} },
			{ "20%", juce::Range<int>{1000, 20000} },
		};

		juce::Atomic<bool> isQuarterNote{ false };		
			
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
	};
}  // namespace sky_trem


/*
quarter note event
1/4: 120000
quarter note event
1/4: 144000
quarter note event
1/4: 168000
quarter note event
1/4: 192000
bar event
Bar: 192000
https://forum.juce.com/t/sending-signal-events-from-audio-to-gui-thread/27792/7
*/