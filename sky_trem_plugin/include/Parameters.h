#pragma once

namespace sky_trem {
	
	struct Parameters {

		explicit Parameters(juce::AudioProcessor&);
		juce::AudioParameterFloat& modulationRate;
		juce::AudioParameterFloat& modulationDepth;
		juce::AudioParameterFloat& gainInDb;
		juce::AudioParameterBool& bypass;
		juce::AudioParameterChoice& lfoWaveform;
		juce::AudioParameterChoice& bpmDivision;
		// represents the state of Rate in HZ or Bpm Division for calculating modRate
		juce::AudioParameterBool& isRateInHz;
		juce::AudioParameterFloat& bpm;

		juce::AudioParameterBool& isModDepthRando;
		juce::AudioParameterChoice& modDepthRandoRange;

		JUCE_DECLARE_NON_COPYABLE(Parameters);
		JUCE_DECLARE_NON_MOVEABLE(Parameters);
	};

}  // namespace sky_trem
