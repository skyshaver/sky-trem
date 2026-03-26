
namespace sky_trem {
	void sky_trem::SkyRotarySlider01::paint(juce::Graphics& g) {

		auto sliderPos = static_cast<float>(valueToProportionOfLength(getValue()));
		jassert(sliderPos >= 0 && sliderPos <= 1.f);

		const auto rotaryParams = getRotaryParameters();
		const auto rotaryStartAngle = rotaryParams.startAngleRadians;
		const auto rotaryEndAngle = rotaryParams.endAngleRadians;


		auto outline = findColour(Slider::rotarySliderOutlineColourId);
		auto fill = findColour(Slider::rotarySliderFillColourId);

		auto bounds = getLocalBounds().toFloat().reduced(10);

		auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
		auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		auto lineW = juce::jmin(8.0f, radius * 0.5f);
		// auto arcRadius = radius - lineW * 0.5f;

		//juce::Path backgroundArc;
		//backgroundArc.addCentredArc(bounds.getCentreX(),
		//	bounds.getCentreY(),
		//	arcRadius,
		//	arcRadius,
		//	0.0f,
		//	rotaryStartAngle,
		//	rotaryEndAngle,
		//	true);

		//g.setColour(outline);
		//g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

		if (isEnabled())
		{
			juce::Path valueArc;
			// valueArc.addPieSegment(getLocalBounds().toFloat(), rotaryStartAngle, toAngle, 0.f);
			//valueArc.addCentredArc(bounds.getCentreX(),
			//	bounds.getCentreY(),
			//	arcRadius,
			//	arcRadius,
			//	0.0f,
			//	rotaryStartAngle,
			//	toAngle,
			//	true);

			valueArc.addArc(bounds.getX(),
				bounds.getY(),
				bounds.getWidth(),
				bounds.getHeight(),
				rotaryStartAngle,
				toAngle,
				true
			);

			g.setColour(fill);
			g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
			// g.fillPath(valueArc);
		}

		//auto thumbWidth = lineW * 2.0f;
		//juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
		//	bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

		//g.setColour(findColour(Slider::thumbColourId));
		//g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));

	}
} // sky_trem