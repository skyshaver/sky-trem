
namespace sky_trem {
	
	// it may make more sense for this to live in Parameters as we have dangerous separation of redundant info
	namespace {
		struct SerializableParameters {
			float modulationRate;
			float gainInDb;
			bool bypass;
			juce::String lfoWaveform;

			static constexpr auto marshallingVersion = 1; //set to std::null_opt to avoid serializing __version__

			template <typename Archive, typename T>
			static void serialise(Archive& archive, T& t) {
				if (archive.getVersion() != marshallingVersion) {
					return;
				}
				std::string pluginName = PLUGIN_NAME;

				if (pluginName != PLUGIN_NAME) {
					return;
				}

				archive(juce::named("pluginName", pluginName));
				archive(juce::named("modulationRate", t.modulationRate), 
					juce::named("gainInDb", t.gainInDb), 
					juce::named("bypass", t.bypass), 
					juce::named("lfoWaveform", t.lfoWaveform));

			}
		};

		SerializableParameters from(const sky_trem::Parameters& parameters) {
			return {
				.modulationRate = parameters.modulationRate.get(),
				.gainInDb = parameters.gainInDb.get(),
				.bypass = parameters.bypass.get(),
				.lfoWaveform = parameters.lfoWaveform.getCurrentChoiceName()
			};
		}
	}

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

		if (parsedParamaters.has_value()) {
			parameters.modulationRate = parsedParamaters->modulationRate;
			parameters.gainInDb = parsedParamaters->gainInDb;
			parameters.bypass = parsedParamaters->bypass;
			parameters.lfoWaveform = parameters.lfoWaveform.choices.indexOf(parsedParamaters->lfoWaveform);
			return juce::Result::ok();
		}
		
		return juce::Result::fail("failed to parse parameters from json");

	}
}  // namespace sky_trem
