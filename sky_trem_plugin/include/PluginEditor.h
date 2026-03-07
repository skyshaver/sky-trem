#pragma once

namespace sky_trem {

	class PluginEditor : public juce::AudioProcessorEditor {

	public:
		explicit PluginEditor(PluginProcessor&);

		void resized() override;

	private:

		class ModulationRateSliderListener : public juce::Slider::Listener {
		public:
			ModulationRateSliderListener(juce::Slider& s) {
				s.addListener(this);
			}

			~ModulationRateSliderListener() override {
				slider.removeListener(this);
			}

			void sliderValueChanged(juce::Slider* slider) override {
				DBG("Rate Slider Value: " << slider->getValue());
			}
		private:
			juce::Slider& slider;
		};

		juce::ImageComponent background;
		juce::ImageComponent logo;

		LfoVisualizer lfoVisualizer;

		juce::Slider modulationRateSlider;
		juce::Slider strokeWidthSlider;
		ModulationRateSliderListener modulationRateSliderListener { modulationRateSlider };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)

	};
}  // namespace sky_trem
