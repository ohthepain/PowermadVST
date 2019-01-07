/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ArpEditor.h"

enum class JoystickId {
	First,
	Left=First,
	Right,
	Count
};

enum class JoystickDirection {
	First,
	Left=First,
	Right,
	Up,
	Down,
	Count
};

class NewProjectAudioProcessorEditor  : public AudioProcessorEditor
, private Button::Listener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& processor;
	
	ArpEditor* arpEditor;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
	
	// Utilities
	static const int kNumJoysticks = 2;
	static const int kNumJoystickButtons = 4;
	ArrowButton* arrowButtons[kNumJoysticks][kNumJoystickButtons];
	void buttonClicked (Button*) override;
	
	int GetJoystickButtonX(int joystickId, int joystickDirection) const;
	int GetJoystickButtonY(int joystickId, int joystickDirection) const;
	int GetJoytsickButtonWidth(int joystickId, int joystickDirection) const;
	int GetJoytsickButtonHeight(int joystickId, int joystickDirection) const;
};
