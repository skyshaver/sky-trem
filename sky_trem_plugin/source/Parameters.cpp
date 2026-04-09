
namespace sky_trem {

	namespace {
		auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {

			auto& result = *parameter;
			processor.addParameter(parameter.release());
			return result;

		}
	}

	juce::AudioParameterFloat& createModulationRateParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.rate", Parameters::versionHint },
				"Modulation Rate",
				juce::NormalisableRange<float>{ .1f, 20.f, .01f, .4f },
				10.f,
				juce::AudioParameterFloatAttributes{}.withLabel("Hz")));

	}

	juce::AudioParameterFloat& createModulationDepthParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.depth", Parameters::versionHint },
				"Modulation Depth",
				juce::NormalisableRange<float>{ 0.f, 1.f, .01f },
				0.4f,
				juce::AudioParameterFloatAttributes{}.withLabel("Depth")));

	}

	juce::AudioParameterFloat& createGainInDbParameter(juce::AudioProcessor& processor) {

		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "gainInDb.value", Parameters::versionHint },
				"Gain in dB",
				juce::NormalisableRange<float>{-12.f, 12.f, .1f},
				0.f,
				juce::AudioParameterFloatAttributes{}.withLabel("dB")));

	}

	juce::AudioParameterBool& createbypassParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterBool>(
				juce::ParameterID{ "bypass", Parameters::versionHint },
				"Bypass",
				false));

	}

	juce::AudioParameterChoice& createLfoWaveformParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "modulation.waveform", Parameters::versionHint },
				"Modulation Waveform",
				juce::StringArray{ "Sine", "Triangle", "Square", "Sawtooth" },
				1));

	}

	/*
	* at 120bpm
	* bpm / 240 is 1/1 (.5hz)
	* bpm / 179.1045 is . 1/2 (.67hz)
	* bpm / 120 is 1/2 (1hz)
	* bpm / 90.2256 is . 1/4 (1.33hz)
	* bpm / 60 is 1/4 (2hz)
	* bpm / 44.9438 is . 1/8 (2.67hz)
	* bpm / 30 is 1/8 (4hz)
	* bpm / 22.5141 is . 1/16 (5.33hz)
	* bpm / 15 is 1/16 (8hz)
	* bpm / 11.2465 is . 1/32 (10.67hz)
	* bpm / 7.5 is 1/32 (16hz)
	* can maybe add a toggle to switch to triplets?
	* https://www.harmoniccycle.com/hc/music-07-tempo_and_note_length.htm
	* juce::StringArray{ "0.0625", "0.125", "0.25", "0.5", "1.0", "1.0625", "1.125", "1.25", "1.5", "2.0" } original bpm division
	* juce::StringArray{ "7.5", "11.2465", "15", "22.5141", "30", "44.9438", "60", "90.2256", "120", "179.1045", "240", } this was moved to pp
	*/
	
	juce::AudioParameterChoice& createBpmDivisionParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "modulation.division", Parameters::versionHint },
				"Modulation Division",				
				juce::StringArray{ "1/32", ".1/32", "1/16", ".1/16", "1/8", ".1/8", "1/4", ".1/4", "1/2", ".1/2", "1/1", },
				6));

	}

	juce::AudioParameterBool& createIsRateInHzParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterBool>(
				juce::ParameterID{ "isRateInHz", Parameters::versionHint },
				"Beat Sync Toggle",
				false));

	}

	juce::AudioParameterFloat& createBpmParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "localBpm", Parameters::versionHint },
				"Local BPM",
				juce::NormalisableRange<float>{ 20.f, 300.f, .01f },
				120.f
			));

	}

	juce::AudioParameterBool& createIsModDepthRandoParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterBool>(
				juce::ParameterID{ "moddepthrando.engaged", Parameters::versionHint },
				"ModDepth Rando Toggle",
				false));

	}

	juce::AudioParameterChoice& createModDepthRandoRangeParameter(juce::AudioProcessor& processor) {
		
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "moddepthrando.range", Parameters::versionHint },
				"Modulation Depth Rando Range",
				juce::StringArray{ "3%", "5%", "10%", "20%" },
				0));

	}

	Parameters::Parameters(juce::AudioProcessor& processor) :
		modulationRate{ createModulationRateParameter(processor) },
		modulationDepth{ createModulationDepthParameter(processor) },
		gainInDb{ createGainInDbParameter(processor) },
		bypass{ createbypassParameter(processor) },
		lfoWaveform{ createLfoWaveformParameter(processor) },
		bpmDivision{ createBpmDivisionParameter(processor) },
		isRateInHz{ createIsRateInHzParameter(processor) },
		bpm{ createBpmParameter(processor) },
		isModDepthRando{ createIsModDepthRandoParameter(processor)},
		modDepthRandoRange { createModDepthRandoRangeParameter(processor) }
	{}

}  // namespace sky_trem
