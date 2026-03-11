#pragma once

namespace sky_trem {
	class CustomLookAndFeel : public juce::LookAndFeel_V4 {
	public:
		void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
			bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
			const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

	};
}  // namespace sky_trem
