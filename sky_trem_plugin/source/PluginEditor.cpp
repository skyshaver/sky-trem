
namespace sky_trem {

	PluginEditor::PluginEditor(PluginProcessor& p)
		: AudioProcessorEditor(&p),
		modulationRateSliderAttachment{ p.getParameterRefs().modulationRate, modulationRateSlider },
		modulationDepthSliderAttachement{ p.getParameterRefs().modulationDepth, modulationDepthSlider },
		gainInDbSliderAttachment{ p.getParameterRefs().gainInDb, gainInDbSlider }, 
		bypassParameterAttachment{p.getParameterRefs().bypass, bypassButton } {

		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		modulationRateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		modulationRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationRateSlider.setPopupDisplayEnabled(true, true, this);
		modulationRateSlider.setTextValueSuffix(" Hz");

		modulationDepthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		modulationDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationDepthSlider.setPopupDisplayEnabled(true, true, this);
		modulationDepthSlider.setTextValueSuffix(" Depth");

		gainInDbSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		gainInDbSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		gainInDbSlider.setPopupDisplayEnabled(true, true, this);
		gainInDbSlider.setTextValueSuffix(" dB");

		bypassButton.onClick = [this]() {
			bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypass On" : "Bypass");
			};
		bypassButton.onClick();
		
		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(modulationRateSlider);
		addAndMakeVisible(modulationDepthSlider);
		addAndMakeVisible(gainInDbSlider);
		addAndMakeVisible(bypassButton);		
		addAndMakeVisible(lfoVisualizer);


		setLookAndFeel(&lookAndFeel);
		setSize(540, 270);		

	}

	PluginEditor::~PluginEditor() {
		setLookAndFeel(nullptr);
	}

	void PluginEditor::resized() {

		const auto bounds = getLocalBounds();
		auto modulationRateSliderBounds = bounds;
		auto modulationDepthSliderBounds = bounds;
		auto gainInDbSliderBounds = bounds;
		auto strokeWidthSliderBounds = bounds;
		auto bypassButtonBounds = bounds;

		auto backgroundBounds = bounds;		
		background.setBounds(backgroundBounds);

		logo.setBounds({ 16, 16, 105, 24 });

		bypassButtonBounds.removeFromLeft(392);
		bypassButtonBounds.removeFromRight(16);
		bypassButtonBounds.removeFromTop(10);
		bypassButtonBounds.removeFromBottom(226);
		bypassButton.setBounds(bypassButtonBounds);
				
		modulationRateSliderBounds.removeFromLeft(230);
		modulationRateSliderBounds.removeFromRight(230);
		modulationRateSliderBounds.removeFromTop(40);
		modulationRateSliderBounds.removeFromBottom(150);
		modulationRateSlider.setBounds(modulationRateSliderBounds);

		modulationDepthSliderBounds.removeFromLeft(16);
		modulationDepthSliderBounds.removeFromRight(bounds.getRight() / 3 * 2);
		modulationDepthSliderBounds.removeFromTop(40);
		modulationDepthSliderBounds.removeFromBottom(150);
		modulationDepthSlider.setBounds(modulationDepthSliderBounds);

		gainInDbSliderBounds.removeFromLeft(bounds.getRight() / 3 * 2);
		gainInDbSliderBounds.removeFromRight(16);
		gainInDbSliderBounds.removeFromTop(40);
		gainInDbSliderBounds.removeFromBottom(150);
		gainInDbSlider.setBounds(gainInDbSliderBounds);
		
		strokeWidthSliderBounds.removeFromLeft(16);
		strokeWidthSliderBounds.removeFromRight(bounds.getRight() / 2);
		strokeWidthSliderBounds.removeFromTop(270);
		strokeWidthSliderBounds.removeFromBottom(0);
		strokeWidthSlider.setBounds(strokeWidthSliderBounds);

		lfoVisualizer.setBounds({ 18, 149, 504, 92 });

	}

}  // namespace sky_trem
