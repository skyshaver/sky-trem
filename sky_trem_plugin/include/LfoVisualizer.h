#pragma once

namespace sky_trem {

	class LfoVisualizer : public juce::Component {

		public:
			void paint(juce::Graphics& g) override;
			void resized() override;

	private:
		const float strokeWidth = 4.f;
		juce::Path sine;



	};
}