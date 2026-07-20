#pragma once

namespace sky_trem {
	
	struct Parameters {

		explicit Parameters(juce::AudioProcessor&);

		//--start parameters
		juce::AudioParameterFloat& modulationRate;
		juce::AudioParameterFloat& modulationDepth;
		juce::AudioParameterFloat& gainInDb;
		juce::AudioParameterBool& bypass;
		juce::AudioParameterChoice& lfoWaveform;
		juce::AudioParameterChoice& bpmDivision;		
		juce::AudioParameterBool& isRateInHz;
		juce::AudioParameterFloat& bpm;
		juce::AudioParameterBool& isModDepthRando;
		juce::AudioParameterChoice& modDepthRandoRange;
		//--stop parameters
		static constexpr int versionHint = 1;

		JUCE_DECLARE_NON_COPYABLE(Parameters);
		JUCE_DECLARE_NON_MOVEABLE(Parameters);
	};

}  // namespace sky_trem
