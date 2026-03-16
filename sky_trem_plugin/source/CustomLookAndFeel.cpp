
// https://github.com/juce-framework/JUCE/blob/master/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp

namespace sky_trem {

	CustomLookAndFeel::CustomLookAndFeel() {
		setColour(juce::PopupMenu::backgroundColourId, juce::Colour{ 0xFF153245 });
		setColour(juce::PopupMenu::textColourId, getCustomColour(CustomColours::paleBlueText));

		setColour(juce::ComboBox::textColourId, getCustomColour(CustomColours::paleBlueText));

		setColour(juce::Label::textColourId, getCustomColour(CustomColours::paleBlueText));

	}

	void sky_trem::CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

		juce::ignoreUnused(shouldDrawButtonAsDown);

		// auto fontSize = juce::jmin(15.0f, static_cast<float>(button.getHeight() * 0.75f));
		const auto bounds = button.getLocalBounds().reduced(2);
		
		std::array<juce::Colour, 3> gradientColours = { getCustomColour(CustomColours::gradientBlueStart), getCustomColour(CustomColours::gradientBlueMiddle),
			getCustomColour(CustomColours::gradientBlueEnd) };
		std::array<juce::Colour, 2> bypassColours = { getCustomColour(CustomColours::gradientOrangeStart), getCustomColour(CustomColours::gradientOrangeEnd)};

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
		
		g.setColour(getCustomColour(CustomColours::paleBlueText));
		g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);

	}

	void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, 
		const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {
	
		auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(3.75f);

		g.setColour(getCustomColour(CustomColours::sliderCanalBlue));
		g.fillEllipse(bounds);

		juce::Path valueArc;
		valueArc.addPieSegment(bounds.toFloat().reduced(0.25f), rotaryStartAngle, toAngle, 0.f);
		g.setColour(getCustomColour(CustomColours::sliderOrange));
		g.fillPath(valueArc);

		g.setColour(getCustomColour(CustomColours::gradientBlueStart));
		g.fillEllipse(bounds.toFloat().reduced(10.f));
	}

	void CustomLookAndFeel::drawRotarySliderOG(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
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

	juce::Colour CustomLookAndFeel::getCustomColour(CustomColours colour)
	{
		switch (colour) {
			case CustomColours::paleBlueText:
				return juce::Colour{ 0xFFDDECFF };
			case CustomColours::darkerBlueText:
				return juce::Colour{ 0xFF6EA0C7 };
			case CustomColours::gradientBlueStart:
				return juce::Colour{ 0xFF4A7090 };
			case CustomColours::gradientBlueMiddle:
				return juce::Colour{ 0xFF315160 };
			case CustomColours::gradientBlueEnd:
				return juce::Colour{ 0xFF324258 };
			case CustomColours::gradientOrangeStart:
				return juce::Colour{ 0xFFFF901A };
			case CustomColours::gradientOrangeEnd:
				return juce::Colour{ 0xFFFFC300 };
			case CustomColours::sliderOrange:
				return juce::Colour{ 0xFFFFAA00 };
			case CustomColours::sliderCanalBlue:
				return juce::Colour{ 0xFF2A3A3B };
			default:
				return juce::Colour{ juce::Colours::white };
		}
	}

}  // namespace sky_trem
