
namespace sky_trem {
	
	void sky_trem::LfoVisualizer::paint(juce::Graphics& g) {
		// g.fillAll(juce::Colours::orange);
		
		g.strokePath(sine, juce::PathStrokeType{ strokeWidth });

	}
	
	void sky_trem::LfoVisualizer::drawSine() {
		sine.clear();

		const auto amplitude = (getHeight() / 2) - (strokeWidth / 2);
		const auto shift = getHeight() / 2.f;
		sine.startNewSubPath(-1.f, shift + amplitude * std::sin(0.f));

		for (const auto i : std::views::iota(1, getWidth() + 1.f)) {
			sine.lineTo(static_cast<float>(i), shift + amplitude * std::sin(0.1f * i)); // remove phase multiplier to get jagged effect (0.1f)
		}
	}

	void sky_trem::LfoVisualizer::resized() {
		
		drawSine();

	}

	

	void sky_trem::LfoVisualizer::setStrokeWidth(float sw) {

		strokeWidth = sw;
		
		drawSine();
		
		repaint();

	}


}