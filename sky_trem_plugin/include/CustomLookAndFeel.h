#pragma once

namespace sky_trem {
	class CustomLookAndFeel : public juce::LookAndFeel_V4 {
	public:

		CustomLookAndFeel();

		void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
			bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

		void drawComboBox(juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override;

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

		void drawRotarySliderOG(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);

		juce::Font getComboBoxFont(juce::ComboBox& box) override {
			juce::ignoreUnused(box);
			return customFont().withPointHeight(12.f);
		}

		void positionComboBoxText(juce::ComboBox& box, juce::Label& labelToPosition) override;

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
			sliderCanalBlue,
			insetBlueStart,
			insetBlueMiddle,
			insetBlueEnd
		};

		static juce::Colour getCustomColour(CustomColours colour);

	private:
		void drawButtonInset(juce::Graphics& g, const juce::Rectangle<float> bounds);
		void drawBlueGradientButton(juce::Graphics& g, const juce::Rectangle<float> bounds, bool shouldDrawButtonAsHighlighted);
		void drawOrangeGradientButton(juce::Graphics& g, const juce::Rectangle<float> bounds, bool shouldDrawButtonAsHighlighted);

	};
}  // namespace sky_trem
