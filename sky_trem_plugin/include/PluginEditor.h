#pragma once

namespace sky_trem {

	class PluginEditor : public juce::AudioProcessorEditor {

	public:
		explicit PluginEditor(PluginProcessor&);
		~PluginEditor() override;

		void resized() override;

	private:

		juce::ImageComponent background;
		juce::ImageComponent logo;

		LfoVisualizer lfoVisualizer;

		juce::Slider modulationRateSlider;
		juce::SliderParameterAttachment modulationRateSliderAttachment;
		juce::Label modulationRateLabel{ "modulation rate label", "RATE" };

		juce::Slider bpmDivisionSlider;
		juce::SliderParameterAttachment bpmDivisionSliderAttachment;
		juce::Label bpmDivisionLabel{ "bpm division label", "BPM DIVISION" };

		juce::Slider modulationDepthSlider;
		juce::SliderParameterAttachment modulationDepthSliderAttachement;
		juce::Label modulationDepthLabel{ "mod depth label", "DEPTH" };

		juce::Slider gainInDbSlider;
		juce::SliderParameterAttachment gainInDbSliderAttachment;
		juce::Label gainInDbLabel{ "gain label", "GAIN" };

		juce::ToggleButton bypassButton;
		juce::ButtonParameterAttachment bypassParameterAttachment;

		juce::ComboBox lfoWaveformCombo;
		juce::ComboBoxParameterAttachment lfoWaveformParameterAttachment;
		juce::Label lfoWaveformLabel{"lfowaveform label","WAVEFORM"};

		// TODO: make this a parameter etc.
		// THIS IS FOR TESTING DO NOT LEAVE IT LIKE THIS
		juce::ToggleButton rateChoiceToggle;
		juce::ButtonParameterAttachment rateChoiceParameterAttachment;
		

		CustomLookAndFeel lookAndFeel;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)

	};
}  // namespace sky_trem
