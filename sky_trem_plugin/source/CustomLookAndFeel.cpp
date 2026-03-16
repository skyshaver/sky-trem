
// https://github.com/juce-framework/JUCE/blob/master/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp

namespace sky_trem {
	/*
	* bounds of button are 132 x 28px
	* margin of 2px
	* rounded rectangle, corner radius of 4px
	* text colour #DDECFF
	* bg gradient, 3 stops, 0% #4A7090, 73% #315160, 100% #324258
	* juce uses ARGB 0xAARRGGBB
	* B4 for 70% opacity or use "withMultipliedAlpha" member function
	*/	

	void sky_trem::CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

		juce::ignoreUnused(shouldDrawButtonAsDown);

		// auto fontSize = juce::jmin(15.0f, static_cast<float>(button.getHeight() * 0.75f));
		const auto bounds = button.getLocalBounds().reduced(2);

		auto textColour = juce::Colour{ 0xFFDDECFF };
		std::array<juce::Colour, 3> gradientColours = { juce::Colour{0xFF4A7090}, juce::Colour{0xFF315160} , juce::Colour{0xFF324258} };
		std::array<juce::Colour, 2> bypassColours = { juce::Colour{0xFFFF901A}, juce::Colour{0xFFFFC300} };

		if (shouldDrawButtonAsHighlighted) {
			std::transform(gradientColours.begin(), gradientColours.end(), gradientColours.begin(), [](auto& colour) { return colour.withMultipliedAlpha(0.7f); });
			std::transform(bypassColours.begin(), bypassColours.end(), bypassColours.begin(), [](auto& colour) { return colour.withMultipliedAlpha(0.7f); });
		}

		auto buttonGradient = juce::ColourGradient::vertical(gradientColours[0], gradientColours[2], bounds);
		buttonGradient.addColour(.73, gradientColours[1]);

		auto bypassGradient = juce::ColourGradient::vertical(bypassColours[0], bypassColours[1], bounds);

		button.getToggleState() ? g.setGradientFill(bypassGradient) : g.setGradientFill(buttonGradient);
		g.fillRoundedRectangle(bounds.toFloat(), 4);

		
		g.setFont(customFont().withPointHeight(12.0));
		// g.setFont(juce::FontOptions{ juce::Typeface::createSystemTypefaceFor(assets::InterMedium_ttf, assets::InterMedium_ttfSize) }.withPointHeight(12.0));
		// auto name = g.getCurrentFont().getTypefacePtr()->getName();
		
		g.setColour(textColour);		
		g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);

	}

	void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {

		auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
		auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

		auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

		auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
		auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		auto lineW = juce::jmin(8.0f, radius * 0.5f);
		auto arcRadius = radius - lineW * 0.5f;

		juce::Path backgroundArc;
		backgroundArc.addCentredArc(bounds.getCentreX(),
			bounds.getCentreY(),
			arcRadius,
			arcRadius,
			0.0f,
			rotaryStartAngle,
			rotaryEndAngle,
			true);

		g.setColour(outline);
		g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

		if (slider.isEnabled())
		{
			juce::Path valueArc;
			valueArc.addCentredArc(bounds.getCentreX(),
				bounds.getCentreY(),
				arcRadius,
				arcRadius,
				0.0f,
				rotaryStartAngle,
				toAngle,
				true);

			g.setColour(fill);
			g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
		}

		// thumb is pointer on wheel
		//auto thumbWidth = lineW * 2.0f;
		//juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
		//	bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

		//g.setColour(slider.findColour(juce::Slider::thumbColourId));
		//g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));

	}

	juce::FontOptions CustomLookAndFeel::customFont() {
		static const auto typefacePtr = juce::Typeface::createSystemTypefaceFor(assets::InterMedium_ttf, assets::InterMedium_ttfSize);

		return juce::FontOptions{ typefacePtr };
	}

}  // namespace sky_trem
