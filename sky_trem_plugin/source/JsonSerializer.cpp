
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
				archive(juce::named("pluginName", PLUGIN_NAME));
				archive(juce::named("modulationRate", t.modulationRate), juce::named("gainInDb", t.gainInDb), juce::named("bypass", t.bypass), juce::named("lfoWaveform", t.lfoWaveform));

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
		const auto parametersToSerialize = from(parameters);
		const auto json = juce::ToVar::convert(parametersToSerialize);
		if (!json.has_value()) {
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

		return juce::Result::fail("not implemented");
	}
}  // namespace sky_trem
