#pragma once

namespace sky_trem {
	class JsonSerializer {
	public:
		static void serialize(const Parameters& parameters, juce::OutputStream& output);

		/** @return Error message on failure; empty string otherwise.
		 *           In case of error, no parameters are updated. */
		static juce::Result deserialize(juce::InputStream& input, Parameters& parameters);
	};
}  // namespace sky_trem
