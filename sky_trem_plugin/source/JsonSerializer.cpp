// it may make more sense for this to live in Parameters as we have dangerous separation of redundant info
namespace {
	struct SerializableParameters {
		float modulationRate;
		float modulationDepth;
		float gainInDb;
		bool bypass;
		juce::String lfoWaveform;

		static constexpr auto marshallingVersion = 1; //set to std::null_opt to avoid serializing __version__

		template <typename Archive, typename T>
		static void serialise(Archive& archive, T& p) {
			if (archive.getVersion() != 1) {
				return;
			}
			std::string pluginName = PLUGIN_NAME;

			archive(juce::named("pluginName", pluginName));

			if (pluginName != PLUGIN_NAME) {
				return;
			}

			archive(juce::named("modulationRate", p.modulationRate),
				juce::named("modulationDepth", p.modulationDepth),
				juce::named("gainInDb", p.gainInDb),
				juce::named("bypass", p.bypass),
				juce::named("lfoWaveform", p.lfoWaveform));

		}
	};

	SerializableParameters from(const sky_trem::Parameters& parameters) {
		return {
			.modulationRate = parameters.modulationRate.get(),
			.modulationDepth = parameters.modulationDepth.get(),
			.gainInDb = parameters.gainInDb.get(),
			.bypass = parameters.bypass.get(),
			.lfoWaveform = parameters.lfoWaveform.getCurrentChoiceName(),
		};
	}
}

namespace sky_trem {


	void JsonSerializer::serialize(const Parameters& parameters, juce::OutputStream& output) {
		const auto json = juce::ToVar::convert(from(parameters));

		if (!json.has_value()) {
			DBG("failed to serialize json");
			return;
		}

		juce::JSON::writeToStream(output, *json, juce::JSON::FormatOptions{}.withSpacing(juce::JSON::Spacing::multiLine).withMaxDecimalPlaces(2));
	}

	juce::Result JsonSerializer::deserialize(juce::InputStream& input, Parameters& parameters) {
		juce::var parsedResult;
		
		const auto result = juce::JSON::parse(input.readEntireStreamAsString(), parsedResult);

		if (result.failed()) {
			return result;
		}

		const auto parsedParamaters = juce::FromVar::convert<SerializableParameters>(parsedResult);

		if (!parsedParamaters.has_value()) {
			return juce::Result::fail("failed to parse parameters from json");
		}
		
		const auto lfoWaveformIndex = parameters.lfoWaveform.choices.indexOf(parsedParamaters->lfoWaveform);
		if (lfoWaveformIndex < 0) {			
			return juce::Result::fail(
				"invalid modulation waveform name; supported values are: " +
				parameters.lfoWaveform.choices.joinIntoString(", "));
		}

		
		parameters.modulationRate = parsedParamaters->modulationRate;
		parameters.modulationDepth = parsedParamaters->modulationDepth;
		parameters.gainInDb = parsedParamaters->gainInDb;
		parameters.bypass = parsedParamaters->bypass;
		parameters.lfoWaveform = lfoWaveformIndex;
		return juce::Result::ok();
		
	}
}  // namespace sky_trem
