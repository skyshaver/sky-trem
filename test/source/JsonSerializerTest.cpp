#include <sky_trem_plugin/sky_trem_plugin.h>
#include <gtest/gtest.h>

namespace sky_trem {
	TEST(JsonSerializer, SerializeToString) {
		PluginProcessor processor;
		auto& parameters = processor.getParameterRefs();

		parameters.modulationRate = 10.f;
		parameters.modulationDepth = 0.5f;
		parameters.gainInDb = 0.f;
		parameters.bypass = true;
		parameters.lfoWaveform = 1;
		parameters.bpmDivision = 1;
		parameters.isRateInHz = true;
		parameters.bpm = 120.f;

		const juce::String expectedOutput =
			u8R"({
  "__version__": 1,
  "pluginName": "SkyTrem",
  "modulationRate": 10.0,
  "modulationDepth": 0.5,
  "gainInDb": 0.0,
  "bypass": true,
  "lfoWaveform": "Triangle",
  "bpmDivision": "0.125",
  "isRateInHz": true,
  "bpm": 120.0
})";
		juce::MemoryBlock block;
		juce::MemoryOutputStream outputStream{ block, false };

		JsonSerializer::serialize(parameters, outputStream);
		outputStream.flush();

		const auto result = outputStream.toUTF8().removeCharacters("\r");

		EXPECT_EQ(expectedOutput, result);
	}

	TEST(JsonSerializer, DeserializeFromString) {
		const juce::String savedParameters =
			u8R"({
  "__version__": 1,
  "pluginName": "SkyTrem",
  "modulationRate": 10.0,
  "modulationDepth": 0.5,
  "gainInDb": 0.0,
  "bypass": true,
  "lfoWaveform": "Triangle",
  "bpmDivision": "0.125",
  "isRateInHz": true,
  "bpm": 120.0
})";

		juce::MemoryInputStream inputStream{
			savedParameters.getCharPointer(),
			static_cast<size_t>(savedParameters.length()), false };

		PluginProcessor processor;
		auto& parameters = processor.getParameterRefs();

		const auto result = JsonSerializer::deserialize(inputStream, parameters);

		EXPECT_TRUE(result.wasOk());
		EXPECT_FLOAT_EQ(parameters.modulationRate, 10.f);
		EXPECT_FLOAT_EQ(parameters.modulationDepth, 0.5f);
		EXPECT_FLOAT_EQ(parameters.gainInDb, 0.f);
		EXPECT_TRUE(parameters.bypass);
		EXPECT_EQ(juce::String{ "Triangle" }, parameters.lfoWaveform.getCurrentChoiceName());
		EXPECT_EQ(juce::String{ "0.125" }, parameters.bpmDivision.getCurrentChoiceName());
		EXPECT_TRUE(parameters.isRateInHz);
		EXPECT_FLOAT_EQ(parameters.bpm, 120.f);
	}

	TEST(JsonSerializer, DontUpdateParametersWhenWaveformNameIsInvalid) {
		// given
		const juce::String savedParameters =
			u8R"({
  "__version__": 1,
  "pluginName": "SkyTrem",
  "modulationRate": 10.0,
  "modulationDepth": 0.5,
  "gainInDb": 0.0,
  "bypass": true,
  "lfoWaveform": "Foo",
  "bpmDivision": "0.125"
})";

		juce::MemoryInputStream inputStream{ savedParameters.getCharPointer(), static_cast<size_t>(savedParameters.length()), false };

		PluginProcessor processor;
		auto& parameters = processor.getParameterRefs();
		parameters.lfoWaveform = 0;
		parameters.bypass = false;
		parameters.modulationRate = 5.f;

		// when
		const auto result = JsonSerializer::deserialize(inputStream, parameters);

		// then
		EXPECT_TRUE(result.failed());
		EXPECT_FLOAT_EQ(parameters.modulationRate.get(), 5.f);
		EXPECT_FALSE(parameters.bypass.get());
		EXPECT_EQ(0, parameters.lfoWaveform.getIndex());
	}

	TEST(JsonSerializer, DontUpdateParametersWhenBpmDivisionIsInvalid) {
		// given
		const juce::String savedParameters =
			u8R"({
  "__version__": 1,
  "pluginName": "SkyTrem",
  "modulationRate": 10.0,
  "modulationDepth": 0.5,
  "gainInDb": 0.0,
  "bypass": true,
  "lfoWaveform": "Triangle",
  "bpmDivision": "foo"
})";

		juce::MemoryInputStream inputStream{ savedParameters.getCharPointer(), static_cast<size_t>(savedParameters.length()), false };

		PluginProcessor processor;
		auto& parameters = processor.getParameterRefs();
		parameters.modulationRate = 5.f;
		parameters.bpmDivision = 1;
		parameters.modulationDepth = 0.5f;
		parameters.gainInDb = 0.f;
		parameters.bypass = false;
		parameters.lfoWaveform = 1;

		// when
		const auto result = JsonSerializer::deserialize(inputStream, parameters);

		// then
		EXPECT_TRUE(result.failed());
		EXPECT_FLOAT_EQ(parameters.modulationRate.get(), 5.f);
		EXPECT_FALSE(parameters.bypass.get());
		EXPECT_EQ(1, parameters.lfoWaveform.getIndex());
	}
}  // namespace sky_trem
