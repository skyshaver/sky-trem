
namespace sky_trem {

	PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {

		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		modulationRateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		modulationRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationRateSlider.setPopupDisplayEnabled(true, true, this);
		modulationRateSlider.setRange(1.f, 30.f, 0.5f);
		modulationRateSlider.onValueChange = [this]() { DBG("Rate Slider Value: " << modulationRateSlider.getValue()); };
		modulationRateSlider.setTextValueSuffix(" Hz");


		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(modulationRateSlider);
		addAndMakeVisible(lfoVisualizer);

		setSize(540, 270);

	}

	void PluginEditor::resized() {
		const auto bounds = getLocalBounds();
		auto modulationRateSliderBounds = bounds;

		background.setBounds(bounds);

		logo.setBounds({ 16, 16, 105, 24 });

		// bounds.removeFromBottom(bounds.getHeight() / 3);
		modulationRateSliderBounds.removeFromLeft(230);
		modulationRateSliderBounds.removeFromRight(230);
		modulationRateSliderBounds.removeFromTop(40);
		modulationRateSliderBounds.removeFromBottom(150);
		modulationRateSlider.setBounds(modulationRateSliderBounds);

		lfoVisualizer.setBounds({ 18, 149, 504, 92 });

	}

}  // namespace sky_trem
