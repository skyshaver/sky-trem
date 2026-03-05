
namespace sky_trem {
	
	PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
		
		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));
		logo_c.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));
		logo_r.setImage(juce::ImageCache::getFromMemory(assets::temp_logo_png, assets::temp_logo_pngSize));

		addAndMakeVisible(background);
		addAndMakeVisible(logo);
		addAndMakeVisible(logo_c);
		addAndMakeVisible(logo_r);

		// Make sure that before the constructor has finished, you've set the
		// editor's size to whatever you need it to be.
		setSize(540, 270);

	}

	void PluginEditor::resized() {
		const auto bounds = getLocalBounds();

		background.setBounds(bounds);

		logo.setBounds({ 16, 16, 105, 24 });
		logo_c.setBounds({ bounds.getCentreX() - (105/2), 16, 105, 24});
		logo_r.setBounds({ bounds.getWidth() - 105 - 16, 16, 105, 24});
	}

}  // namespace sky_trem
