
namespace sky_trem {

	PluginEditor::PluginEditor(PluginProcessor& p)
		: AudioProcessorEditor(&p), modulationRateSliderAttachment{ p.getParameterRefs().modulationRate, modulationRateSlider } {

		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		modulationRateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		modulationRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationRateSlider.setPopupDisplayEnabled(true, true, this);				
		modulationRateSlider.setTextValueSuffix(" Hz");

		strokeWidthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		strokeWidthSlider.setRange(1.f, 30.f, 0.5f);
		// strokeWidthSlider.onValueChange = [this]() { DBG("Stroke Width SLider: " << strokeWidthSlider.getValue()); };
		strokeWidthSlider.onValueChange = [this]() { lfoVisualizer.setStrokeWidth(static_cast<float>(strokeWidthSlider.getValue())); };

		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(strokeWidthSlider);
		addAndMakeVisible(modulationRateSlider);
		addAndMakeVisible(lfoVisualizer);

		// setSize(540, 270);
		setSize(540, 300); // with UI control pane

	}

	void PluginEditor::resized() {

		const auto bounds = getLocalBounds();
		auto modulationRateSliderBounds = bounds;
		auto strokeWidthSliderBounds = bounds;

		auto backgroundBounds = bounds;
		backgroundBounds.removeFromBottom(30);
		background.setBounds(backgroundBounds);

		logo.setBounds({ 16, 16, 105, 24 });

		modulationRateSliderBounds.removeFromLeft(230);
		modulationRateSliderBounds.removeFromRight(230);
		modulationRateSliderBounds.removeFromTop(40);
		modulationRateSliderBounds.removeFromBottom(150);
		modulationRateSlider.setBounds(modulationRateSliderBounds);

		strokeWidthSliderBounds.removeFromLeft(16);
		strokeWidthSliderBounds.removeFromRight(bounds.getRight() / 2);
		strokeWidthSliderBounds.removeFromTop(270);
		strokeWidthSliderBounds.removeFromBottom(0);
		strokeWidthSlider.setBounds(strokeWidthSliderBounds);

		lfoVisualizer.setBounds({ 18, 149, 504, 92 });

	}

}  // namespace sky_trem
