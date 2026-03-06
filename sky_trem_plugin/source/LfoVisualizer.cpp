
namespace sky_trem {
	
	void sky_trem::LfoVisualizer::paint(juce::Graphics& g) {
		// g.fillAll(juce::Colours::orange);
		

		// no need to call clear as componenent is not resizeable
		g.strokePath(sine, juce::PathStrokeType{ strokeWidth });

	}
	void sky_trem::LfoVisualizer::resized() {
		
		const auto amplitude = (getHeight() / 2) - (strokeWidth / 2);
		const auto shift = getHeight() / 2;
		sine.startNewSubPath(-1.f, shift + amplitude * std::sin(0.f));
		for (const auto i : std::views::iota(1, getWidth() + 1.f)) {
			sine.lineTo(i, shift + amplitude * std::sin(0.1f * i)); // remove phase multiplier to get jagged effect (0.1f)
		}
	}
}