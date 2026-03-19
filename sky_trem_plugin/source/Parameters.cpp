
namespace sky_trem {

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
				10.f,
				juce::AudioParameterFloatAttributes{}.withLabel("Hz")));

	}

	juce::AudioParameterFloat& createModulationDepthParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.depth", versionHint },
				"Modulation Depth",
				juce::NormalisableRange<float>{ 0.f, 1.f, .01f },
				0.4f,
				juce::AudioParameterFloatAttributes{}.withLabel("Depth")));

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
				juce::ParameterID{ "bypass", versionHint },
				"Bypass",
				false));

	}

	juce::AudioParameterChoice& createLfoWaveformParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "modulation.waveform", versionHint },
				"Modulation Waveform",
				juce::StringArray{ "Sine", "Triangle", "Square" },
				1));

	}

	juce::AudioParameterChoice& createBpmDivisionParameter(juce::AudioProcessor& processor) {

		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterChoice>(
				juce::ParameterID{ "modulation.division", versionHint },
				"Modulation Division",
				juce::StringArray{ "0.0625", "0.125", "0.25", "0.5", "1.0625", "1.125", "1.25", "1.5" },
				1));

	}

	Parameters::Parameters(juce::AudioProcessor& processor) :
		modulationRate{ createModulationRateParameter(processor) },
		modulationDepth{ createModulationDepthParameter(processor) },
		gainInDb{ createGainInDbParameter(processor) },
		bypass{ createbypassParameter(processor) },
		lfoWaveform{ createLfoWaveformParameter(processor) },
		bpmDivision{ createBpmDivisionParameter(processor) }

	{
	}

}  // namespace sky_trem
