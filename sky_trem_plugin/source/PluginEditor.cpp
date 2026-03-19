
namespace sky_trem {

	PluginEditor::PluginEditor(PluginProcessor& p)
		: AudioProcessorEditor(&p),
		modulationRateSliderAttachment{ p.getParameterRefs().modulationRate, modulationRateSlider },
		bpmDivisionSliderAttachment{ p.getParameterRefs().bpmDivision, bpmDivisionSlider },
		modulationDepthSliderAttachement{ p.getParameterRefs().modulationDepth, modulationDepthSlider },
		gainInDbSliderAttachment{ p.getParameterRefs().gainInDb, gainInDbSlider },
		bypassParameterAttachment{ p.getParameterRefs().bypass, bypassButton },
		lfoWaveformParameterAttachment{ p.getParameterRefs().lfoWaveform, lfoWaveformCombo } {

		background.setImage(juce::ImageCache::getFromMemory(assets::background_blk_png, assets::background_blk_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		lfoWaveformCombo.addItemList(p.getParameterRefs().lfoWaveform.choices, 1);
		lfoWaveformParameterAttachment.sendInitialUpdate();

		bypassButton.onClick = [this]() {
			bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypass On" : "Bypass");
			};
		bypassButton.onClick();

		rateChoiceToggle.onClick = [this]() {
						rateChoiceToggle.setButtonText(rateChoiceToggle.getToggleState() ? "Bpm Division" : "Rate in Hz");
						resized();
			};
		rateChoiceToggle.onClick();

		modulationRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		modulationRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationRateSlider.setPopupDisplayEnabled(true, true, this);
		modulationRateSlider.setTextValueSuffix(" Hz");
		modulationRateLabel.setJustificationType(juce::Justification::centred);
		modulationRateLabel.setInterceptsMouseClicks(false, false);
		modulationRateLabel.setFont(lookAndFeel.getSliderLabelFont());

		bpmDivisionSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		bpmDivisionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		bpmDivisionSlider.setPopupDisplayEnabled(true, true, this);
		bpmDivisionSlider.setTextValueSuffix(" bpm division");
		bpmDivisionLabel.setJustificationType(juce::Justification::centred);
		bpmDivisionLabel.setInterceptsMouseClicks(false, false);
		bpmDivisionLabel.setFont(lookAndFeel.getSliderLabelFont());

		modulationDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
		modulationDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		modulationDepthSlider.setPopupDisplayEnabled(true, true, this);
		modulationDepthSlider.setTextValueSuffix(" Depth");
		modulationDepthLabel.setJustificationType(juce::Justification::centred);
		modulationDepthLabel.setInterceptsMouseClicks(false, false);
		modulationDepthLabel.setFont(lookAndFeel.getSliderLabelFont());

		gainInDbSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
		gainInDbSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
		gainInDbSlider.setPopupDisplayEnabled(true, true, this);
		gainInDbSlider.setTextValueSuffix(" dB");
		gainInDbLabel.setJustificationType(juce::Justification::centred);
		gainInDbLabel.setInterceptsMouseClicks(false, false);
		gainInDbLabel.setFont(lookAndFeel.getSliderLabelFont());

		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(lfoWaveformCombo);
		addAndMakeVisible(lfoWaveformLabel);
		addAndMakeVisible(bypassButton);
		addAndMakeVisible(rateChoiceToggle);
		
		addAndMakeVisible(modulationRateSlider);
		addAndMakeVisible(modulationRateLabel);

		addAndMakeVisible(bpmDivisionSlider);
		addAndMakeVisible(bpmDivisionLabel);

		addAndMakeVisible(modulationDepthSlider);
		addAndMakeVisible(modulationDepthLabel);
		addAndMakeVisible(gainInDbSlider);
		addAndMakeVisible(gainInDbLabel);
		// addAndMakeVisible(lfoVisualizer);		

		setLookAndFeel(&lookAndFeel);
		setSize(300, 600);

	}

	PluginEditor::~PluginEditor() {
		setLookAndFeel(nullptr);
	}

	void PluginEditor::resized() {

		const auto bounds = getLocalBounds();
		auto logoBounds = bounds;
		auto lfoComboBounds = bounds;
		auto bypassButtonBounds = bounds;
		auto rateChoiceToggleBounds = bounds;

		auto modulationRateSliderBounds = bounds;
		auto modulationDepthSliderBounds = bounds;
		auto gainInDbSliderBounds = bounds;

		auto backgroundBounds = bounds;
		background.setBounds(backgroundBounds);

		logoBounds.removeFromLeft(70);
		logoBounds.removeFromRight(70);
		logoBounds.removeFromTop(540);
		logoBounds.removeFromBottom(20);
		logo.setBounds(logoBounds);

		lfoComboBounds.removeFromLeft(50);
		lfoComboBounds.removeFromRight(50);
		lfoComboBounds.removeFromTop(490);
		lfoComboBounds.removeFromBottom(80);
		lfoWaveformCombo.setBounds(lfoComboBounds);

		auto lfoLabelBounds = lfoComboBounds;
		lfoLabelBounds = lfoLabelBounds.translated(0, -lfoComboBounds.getHeight());
		lfoWaveformLabel.setBounds(lfoLabelBounds);

		bypassButtonBounds.removeFromLeft(190);
		bypassButtonBounds.removeFromRight(20);
		bypassButtonBounds.removeFromTop(420);
		bypassButtonBounds.removeFromBottom(160);
		bypassButton.setBounds(bypassButtonBounds);

		rateChoiceToggleBounds.removeFromLeft(190);
		rateChoiceToggleBounds.removeFromRight(20);
		rateChoiceToggleBounds.removeFromTop(390);
		rateChoiceToggleBounds.removeFromBottom(190);
		rateChoiceToggle.setBounds(rateChoiceToggleBounds);

		modulationRateSliderBounds.removeFromLeft(30);
		modulationRateSliderBounds.removeFromRight(220);
		modulationRateSliderBounds.removeFromTop(50);
		modulationRateSliderBounds.removeFromBottom(150);
		modulationRateSlider.setBounds(modulationRateSliderBounds);
		modulationRateLabel.setBounds(modulationRateSliderBounds);
		
		bpmDivisionSlider.setBounds(modulationRateSliderBounds);
		bpmDivisionLabel.setBounds(modulationRateSliderBounds);
				
		// toggle fader between bpm division and rate
		bpmDivisionSlider.setVisible(rateChoiceToggle.getToggleState());
		bpmDivisionLabel.setVisible(rateChoiceToggle.getToggleState());
		modulationRateSlider.setVisible(!rateChoiceToggle.getToggleState());
		modulationRateLabel.setVisible(!rateChoiceToggle.getToggleState());
				
		modulationDepthSliderBounds.removeFromLeft(110);
		modulationDepthSliderBounds.removeFromRight(140);
		modulationDepthSliderBounds.removeFromTop(50);
		modulationDepthSliderBounds.removeFromBottom(150);
		modulationDepthSlider.setBounds(modulationDepthSliderBounds);
		modulationDepthLabel.setBounds(modulationDepthSliderBounds);

		// 70px x 70px
		gainInDbSliderBounds.removeFromLeft(205);
		gainInDbSliderBounds.removeFromRight(25);
		gainInDbSliderBounds.removeFromTop(50);
		gainInDbSliderBounds.removeFromBottom(480);
		gainInDbSlider.setBounds(gainInDbSliderBounds);
		gainInDbLabel.setBounds(gainInDbSliderBounds);


	}

}  // namespace sky_trem
