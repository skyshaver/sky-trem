
namespace tremolo {

	namespace {
		auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
			
			auto& result = *parameter;
			processor.addParameter(parameter.release());
			return result;

		}
	}

	juce::AudioParameterFloat& createModulationRateParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.rate", versionHint }, 
				"Modulation Rate",
				juce::NormalisableRange<float>{ .1f, 20.f, .01f, .4f },
				5.f,
				juce::AudioParameterFloatAttributes{}.withLabel("Hz")));

	}

	juce::AudioParameterFloat& createGainInDbParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "gainInDb.value", versionHint }, 
				"Gain in dB",
				juce::NormalisableRange<float>{-12.f, 12.f, .1f},
				0.f,
				juce::AudioParameterFloatAttributes{}.withLabel("dB")));

	}

	juce::AudioParameterBool& createbypassParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterBool>(
				juce::ParameterID{ "Bypass", versionHint }, 
				"Bypass",
				false ));

	}

	juce::AudioParameterChoice& createLfoWaveformParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "modulation.waveform", versionHint },
				"Modulation Waveform",
				juce::StringArray{ "SINE", "TRIANGLE", "SQUARE" },
				0));

	}

	Parameters::Parameters(juce::AudioProcessor& processor) : 
		modulationRate{ createModulationRateParameter(processor) }, 
		gainInDb{ createGainInDbParameter(processor) }, 
		bypass{ createbypassParameter(processor) },
		lfoWaveform{ createLfoWaveformParameter(processor) }
	{}

}  // namespace tremolo
