
namespace sky_trem {
	
	PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
		
		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));
		

		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(lfoVisualizer);
		setSize(540, 270);

	}

	void PluginEditor::resized() {
		const auto bounds = getLocalBounds();

		background.setBounds(bounds);

		logo.setBounds({ 16, 16, 105, 24 });
		lfoVisualizer.setBounds({ 18, 149, 504, 92 });
		
	}

}  // namespace sky_trem
