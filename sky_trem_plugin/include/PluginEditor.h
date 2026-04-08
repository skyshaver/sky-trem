#pragma once

namespace sky_trem {

	class PluginEditor : public juce::AudioProcessorEditor, private juce::Timer {

	public:
		explicit PluginEditor(PluginProcessor&);
		~PluginEditor() override;

		void resized() override;

		PluginProcessor& pluginProcessor;

		void timerCallback() override;

	private:

		juce::ImageComponent background;
		juce::ImageComponent logo;

		LfoVisualizer lfoVisualizer;

		juce::Slider modulationRateSlider;
		juce::SliderParameterAttachment modulationRateSliderAttachment;
		juce::Label modulationRateLabel{ "modulation rate label", "RATE" };

		juce::Slider bpmDivisionSlider;
		juce::SliderParameterAttachment bpmDivisionSliderAttachment;
		juce::Label bpmDivisionLabel{ "bpm division label", "BEAT SYNC" };

		juce::Slider modulationDepthSlider;
		juce::SliderParameterAttachment modulationDepthSliderAttachement;
		juce::Label modulationDepthLabel{ "mod depth label", "DEPTH" };

		// juce::Slider gainInDbSlider;
		SkyRotarySlider01 gainInDbSlider;
		juce::SliderParameterAttachment gainInDbSliderAttachment;
		juce::Label gainInDbLabel{ "gain label", "GAIN" };

		juce::ToggleButton bypassButton;
		juce::ButtonParameterAttachment bypassParameterAttachment;

		juce::ComboBox lfoWaveformCombo;
		juce::ComboBoxParameterAttachment lfoWaveformParameterAttachment;
		juce::Label lfoWaveformLabel{"lfowaveform label","WAVEFORM"};
		
		juce::ToggleButton rateChoiceToggle;
		juce::ButtonParameterAttachment rateChoiceParameterAttachment;

		juce::ToggleButton modDepthRandoToggle;
		juce::ButtonParameterAttachment modDepthRandoParameterAttachment;

		SkyComboBox01 modDepthRandoRangeCombo;
		juce::ComboBoxParameterAttachment modDepthRandoRangeAttachment;
		
		juce::ShapeButton quarterNoteFlasher{ "flasher", juce::Colours::aliceblue, juce::Colours::antiquewhite, juce::Colours::red };
		bool lightOn{ false };
		bool lastButtonState{ false };

		CustomLookAndFeel lookAndFeel;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)

	};
}  // namespace sky_trem
