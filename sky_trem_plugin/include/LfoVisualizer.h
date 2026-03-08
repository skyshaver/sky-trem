#pragma once

namespace sky_trem {

	class LfoVisualizer : public juce::Component {

	public:
		void paint(juce::Graphics& g) override;
		void resized() override;
		void setStrokeWidth(float sw);

	private:
		float strokeWidth = 1.f;

		juce::Path sine;
		void drawSine();

	};
}