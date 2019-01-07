/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

typedef struct {
	const String buttonName;
	const float direction;
	const JoystickId joystickId;
	const JoystickDirection joystickDirection;
	const String buttonText;
} ArrowButtonDef;

const ArrowButtonDef kArrowButtonDef[] =
{
	{ "left:left", 0.5, JoystickId::Left, JoystickDirection::Left, "LL", },
	{ "left:up", 0.75, JoystickId::Left, JoystickDirection::Up, "LU", },
	{ "left:right", 0.0, JoystickId::Left, JoystickDirection::Right, "LR", },
	{ "left:down", 0.25, JoystickId::Left, JoystickDirection::Down, "LD", },
	{ "right:left", 0.5, JoystickId::Right, JoystickDirection::Left, "RL", },
	{ "right:up", 0.75, JoystickId::Right, JoystickDirection::Up, "RU", },
	{ "right:right", 0.0, JoystickId::Right, JoystickDirection::Right, "RU", },
	{ "right:down", 0.25, JoystickId::Right, JoystickDirection::Down, "RD", },
};

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	Colour joystickButtonColour(100, 100, 100);
	for (int i=0; i<8; i++)
	{
		const ArrowButtonDef& arrowButtonDef = kArrowButtonDef[i];
		ArrowButton* arrowButton = new ArrowButton(arrowButtonDef.buttonName, arrowButtonDef.direction, joystickButtonColour);
		arrowButton->setButtonText(arrowButtonDef.buttonText);
		arrowButton->addListener(this);
		arrowButtons[(int)arrowButtonDef.joystickId][(int)arrowButtonDef.joystickDirection] = arrowButton;
		addAndMakeVisible(arrowButton);
	}
	
	arpEditor = new ArpEditor(this);
	
	setSize(800, 800);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
	for (int i=0; i<(int)JoystickId::Count; i++)
	{
		for (int j=0; j<(int)JoystickDirection::Count; j++)
		{
			delete arrowButtons[i][j];
			arrowButtons[i][j] = nullptr;
		}
	}
	
	delete arpEditor;
	arpEditor = nullptr;
}

void NewProjectAudioProcessorEditor::buttonClicked(Button* button)
{
	Logger::writeToLog(button->getButtonText());
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	arpEditor->paint(g);
}

int NewProjectAudioProcessorEditor::GetJoystickButtonX(int joystickId, int joystickDirection) const
{
	const int kJoystickSpacingX = 140;
	const int kJoystickButtonSpacingX = 40;
	int x = getWidth() / 2 - kJoystickSpacingX;
	if (joystickId == (int)JoystickId::Right)
	{
		x = getWidth() / 2 + kJoystickSpacingX;
	}
	switch ((JoystickDirection)joystickDirection) {
		case JoystickDirection::Left:
			return x - kJoystickButtonSpacingX;
		case JoystickDirection::Right:
			return x + kJoystickButtonSpacingX;
		default:
			return x;
	}
}

int NewProjectAudioProcessorEditor::GetJoystickButtonY(int joystickId, int joystickDirection) const
{
	const int kJoystickButtonSpacingY = 40;
	int y = getHeight() * 2 / 3;
	switch ((JoystickDirection)joystickDirection)
	{
		case JoystickDirection::Up:
			return y - kJoystickButtonSpacingY;
		case JoystickDirection::Down:
			return y + kJoystickButtonSpacingY;
		default:
			return y;
	}
}

int NewProjectAudioProcessorEditor::GetJoytsickButtonWidth(int joystickId, int joystickDirection) const
{
	return 40;
}

int NewProjectAudioProcessorEditor::GetJoytsickButtonHeight(int joystickId, int joystickDirection) const
{
	return 40;
}

void NewProjectAudioProcessorEditor::resized()
{
	for (int i=0; i<(int)JoystickId::Count; i++)
	{
		for (int j=0; j<(int)JoystickDirection::Count; j++)
		{
			int x = GetJoystickButtonX(i, j);
			int y = GetJoystickButtonY(i, j);
			int w = GetJoytsickButtonWidth(i, j);
			int h = GetJoytsickButtonHeight(i, j);
			arrowButtons[i][j]->setBounds(x, y, w, h);
		}
	}
	
	arpEditor->SetRect(0, 0, getWidth(), 450);
}
