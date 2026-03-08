#pragma once

namespace sky_trem {

	class PluginEditor : public juce::AudioProcessorEditor {

	public:
		explicit PluginEditor(PluginProcessor&);

		void resized() override;

	private:

		juce::ImageComponent background;
		juce::ImageComponent logo;

		LfoVisualizer lfoVisualizer;

		juce::Slider modulationRateSlider;		
		juce::SliderParameterAttachment modulationRateSliderAttachment;
		
		juce::Slider strokeWidthSlider;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)

	};
}  // namespace sky_trem
