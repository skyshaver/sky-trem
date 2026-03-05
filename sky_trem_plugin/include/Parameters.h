#pragma once

namespace sky_trem {
	
	struct Parameters {

		explicit Parameters(juce::AudioProcessor&);
		juce::AudioParameterFloat& modulationRate;
		juce::AudioParameterFloat& modulationDepth;
		juce::AudioParameterFloat& gainInDb;
		juce::AudioParameterBool& bypass;
		juce::AudioParameterChoice& lfoWaveform;

		JUCE_DECLARE_NON_COPYABLE(Parameters);
		JUCE_DECLARE_NON_MOVEABLE(Parameters);
	};

}  // namespace sky_trem
