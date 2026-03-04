#pragma once

namespace sky_trem {
class JsonSerializer {
public:
  static void serialize(const Parameters&, juce::OutputStream&);

  /** @return Error message on failure; empty string otherwise.
   *           In case of error, no parameters are updated. */
  static juce::Result deserialize(juce::InputStream&, Parameters&);
};
}  // namespace sky_trem
