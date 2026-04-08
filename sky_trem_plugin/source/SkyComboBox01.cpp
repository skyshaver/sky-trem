
namespace sky_trem {
	void sky_trem::SkyComboBox01::paint(juce::Graphics& g) {

        auto boxBounds = getLocalBounds().toFloat();

        // auto cornerSize = box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
        auto cornerSize = 3.f;
        // juce::Rectangle<int> boxBounds(0, 0, width, height);

        g.setColour(findColour(juce::ComboBox::backgroundColourId));
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

        g.setColour(findColour(juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

        //juce::Rectangle<int> arrowZone(width - 30, 0, 20, height);
        //juce::Path path;
        //path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
        //path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
        //path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

        g.setColour(findColour(juce::ComboBox::arrowColourId).withAlpha((isEnabled() ? 0.9f : 0.2f)));
        // g.strokePath(path, juce::PathStrokeType(2.0f));

	}
} // namepsace sky_trem