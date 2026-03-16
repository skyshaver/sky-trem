#pragma once

namespace sky_trem {
	class CustomLookAndFeel : public juce::LookAndFeel_V4 {
	public:

		CustomLookAndFeel();

		void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
			bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

		void drawRotarySliderOG(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);

		static juce::FontOptions getSliderLabelFont() {
			return customFont().withPointHeight(10.f);
		}

		static juce::FontOptions customFont();

		enum class CustomColours {
			paleBlueText,
			darkerBlueText,
			gradientBlueStart,
			gradientBlueMiddle,
			gradientBlueEnd,
			gradientOrangeStart,
			gradientOrangeEnd,
			sliderOrange,
			sliderCanalBlue
		};

		static juce::Colour getCustomColour(CustomColours colour);

	};
}  // namespace sky_trem
