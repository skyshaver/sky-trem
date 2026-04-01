
namespace sky_trem {

	PluginEditor::PluginEditor(PluginProcessor& p)
		: AudioProcessorEditor(&p),
		pluginProcessor(p),
		modulationRateSliderAttachment{ p.getParameterRefs().modulationRate, modulationRateSlider },
		bpmDivisionSliderAttachment{ p.getParameterRefs().bpmDivision, bpmDivisionSlider },
		modulationDepthSliderAttachement{ p.getParameterRefs().modulationDepth, modulationDepthSlider },
		gainInDbSliderAttachment{ p.getParameterRefs().gainInDb, gainInDbSlider },
		bypassParameterAttachment{ p.getParameterRefs().bypass, bypassButton },
		lfoWaveformParameterAttachment{ p.getParameterRefs().lfoWaveform, lfoWaveformCombo },
		rateChoiceParameterAttachment{p.getParameterRefs().isRateInHz, rateChoiceToggle},
		modDepthRandoParameterAttachment{ p.getParameterRefs().isModDepthRando, modDepthRandoToggle },
		modDepthRandoRangeAttachment{ p.getParameterRefs().modDepthRandoRange, modDepthRandoRangeCombo } {

		background.setImage(juce::ImageCache::getFromMemory(assets::background_blk_png, assets::background_blk_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		lfoWaveformCombo.addItemList(p.getParameterRefs().lfoWaveform.choices, 1);
		lfoWaveformParameterAttachment.sendInitialUpdate();

		modDepthRandoRangeCombo.addItemList(p.getParameterRefs().modDepthRandoRange.choices, 1);
		modDepthRandoRangeAttachment.sendInitialUpdate();

		bypassButton.onClick = [this]() {
				bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypass On" : "Bypass");
			};
		bypassButton.onClick();

		// the way the button overload is setup true is the colored choice
		// so this choice seems non default, will leave for testing but need to make ui consistent
		rateChoiceToggle.onClick = [this]() {
				rateChoiceToggle.setButtonText(rateChoiceToggle.getToggleState() ? "Rate in Hz" : "Beat Sync");
				resized();
			};
		rateChoiceToggle.onClick();

		modDepthRandoToggle.onClick = [this]() {
			modDepthRandoToggle.setButtonText(modDepthRandoToggle.getToggleState() ? "Rando ON" : "Rando OFF");
			};
		modDepthRandoToggle.onClick();


		// stuff for debug light
		startTimerHz(30);
		juce::Path circle;
		circle.addEllipse(50.f, 50.f, 50.f, 50.f);
		quarterNoteFlasher.setShape(circle, true, true, false);


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
		bpmDivisionSlider.setTextValueSuffix(" note");
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

		// gainInDbSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
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
		addAndMakeVisible(modDepthRandoToggle);
		addAndMakeVisible(modDepthRandoRangeCombo);
		addAndMakeVisible(quarterNoteFlasher);
		
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


		auto modRandoToggleBounds = bounds;
		modRandoToggleBounds.removeFromLeft(190);
		modRandoToggleBounds.removeFromRight(20);
		modRandoToggleBounds.removeFromTop(360);
		modRandoToggleBounds.removeFromBottom(220);
		modDepthRandoToggle.setBounds(modRandoToggleBounds);

		auto modRandoRangeBounds = bounds;
		modRandoRangeBounds.removeFromLeft(190);
		modRandoRangeBounds.removeFromRight(20);
		modRandoRangeBounds.removeFromTop(330);
		modRandoRangeBounds.removeFromBottom(250);
		modDepthRandoRangeCombo.setBounds(modRandoRangeBounds);

		modulationRateSliderBounds.removeFromLeft(30);
		modulationRateSliderBounds.removeFromRight(220);
		modulationRateSliderBounds.removeFromTop(50);
		modulationRateSliderBounds.removeFromBottom(150);
		modulationRateSlider.setBounds(modulationRateSliderBounds);
		modulationRateLabel.setBounds(modulationRateSliderBounds);
		
		bpmDivisionSlider.setBounds(modulationRateSliderBounds);
		bpmDivisionLabel.setBounds(modulationRateSliderBounds);
				
		// toggle fader between bpm division and rate
		bpmDivisionSlider.setVisible(!rateChoiceToggle.getToggleState());
		bpmDivisionLabel.setVisible(!rateChoiceToggle.getToggleState());
		modulationRateSlider.setVisible(rateChoiceToggle.getToggleState());
		modulationRateLabel.setVisible(rateChoiceToggle.getToggleState());
				
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

		auto flasherBounds = bounds;
		flasherBounds.removeFromLeft(205);
		flasherBounds.removeFromRight(25);
		flasherBounds.removeFromTop(150);
		flasherBounds.removeFromBottom(380);
		quarterNoteFlasher.setBounds(flasherBounds);


	}

	void PluginEditor::timerCallback() {
			
		lastButtonState = lightOn;
		lightOn = pluginProcessor.getAndResetIsQuarterNote();
		quarterNoteFlasher.setState(lightOn || lastButtonState ? juce::Button::buttonDown : juce::Button::buttonNormal);
		repaint();
	}

}  // namespace sky_trem
