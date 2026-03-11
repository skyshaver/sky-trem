
namespace sky_trem {

	void sky_trem::CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

		auto fontSize = juce::jmin(15.0f, (float)button.getHeight() * 0.75f);
		auto tickWidth = fontSize * 1.1f;

		drawTickBox(g, button, 4.0f, ((float)button.getHeight() - tickWidth) * 0.5f,
			tickWidth, tickWidth,
			button.getToggleState(),
			button.isEnabled(),
			shouldDrawButtonAsHighlighted,
			shouldDrawButtonAsDown);

		g.setColour(button.findColour(juce::ToggleButton::textColourId));
		g.setFont(fontSize);

		if (!button.isEnabled())
			g.setOpacity(0.5f);

		g.drawFittedText(button.getButtonText(),
			button.getLocalBounds().withTrimmedLeft(juce::roundToInt(tickWidth) + 10)
			.withTrimmedRight(2),
			juce::Justification::centredLeft, 10);

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

}  // namespace sky_trem
