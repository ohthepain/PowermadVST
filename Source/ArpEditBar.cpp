//
//  ArpEditBar.cpp
//  NewProject - VST3
//
//  Created by Paul Wilkinson on 1/7/19.
//

#include "ArpEditBar.h"
#include "PowermadEditorDefs.h"

ArpEditBar::ArpEditBar(AudioProcessorEditor* parent)
: ControlGroup()
{
	Colour joystickButtonColour(100, 100, 100);
	noteUpButton = new ArrowButton("ArpEditBar:noteUp", 0.75, joystickButtonColour);
	noteUpButton->addListener(this);
	parent->addAndMakeVisible(noteUpButton);
	noteDownButton = new ArrowButton("ArpEditBar:noteUp", 0.25, joystickButtonColour);
	noteDownButton->addListener(this);
	parent->addAndMakeVisible(noteDownButton);
	noteLeftButton = new ArrowButton("ArpEditBar:noteUp", 0.5, joystickButtonColour);
	noteLeftButton->addListener(this);
	parent->addAndMakeVisible(noteLeftButton);
	noteRightButton = new ArrowButton("ArpEditBar:noteUp", 0.0, joystickButtonColour);
	noteRightButton->addListener(this);
	parent->addAndMakeVisible(noteRightButton);
	
	arpButton = new Button*[kNumArpButtons];
	for (int i=0; i<kNumArpButtons; i++)
	{
		String buttonText;
		buttonText << "[ " << i+1 << " ]";
		arpButton[i] = new TextButton(buttonText);
		arpButton[i]->addListener(this);
		parent->addAndMakeVisible(arpButton[i]);
	}
}

ArpEditBar::~ArpEditBar()
{
	delete noteUpButton;
	noteUpButton = nullptr;
	delete noteDownButton;
	noteDownButton = nullptr;
	delete noteLeftButton;
	noteLeftButton = nullptr;
	delete noteRightButton;
	noteRightButton = nullptr;
	
	for (int i=0; i<kNumArpButtons; i++)
	{
		delete arpButton[i];
		arpButton[i] = nullptr;
	}
	
	delete [] arpButton;
	arpButton = nullptr;
}

void ArpEditBar::SetRect(int x, int y, int w, int h)
{
	ControlGroup::SetRect(x, y, w, h);
	
	int buttonHeight = h - 10;
	int arrowButtonWidth = h - 10;
	
	x = kMinControlSpacingX;
	noteDownButton->setBounds(x, y, arrowButtonWidth, buttonHeight);
	x += arrowButtonWidth;
	noteUpButton->setBounds(x, y, arrowButtonWidth, buttonHeight);
	
	x += arrowButtonWidth + arrowButtonWidth;
	for (int i=0; i<kNumArpButtons; i++)
	{
		arpButton[i]->setBounds(x, y, kTextButtonWidth, buttonHeight);
		x += kTextButtonWidth + kMinControlSpacingX;
	}
	
	x = w - arrowButtonWidth - kMinControlSpacingX;
	noteRightButton->setBounds(x, y, arrowButtonWidth, buttonHeight);
	x -= arrowButtonWidth;
	noteLeftButton->setBounds(x, y, arrowButtonWidth, buttonHeight);
}

void ArpEditBar::SetListener(ArpEditBar::Listener* arpEditBarListener)
{
	listener = arpEditBarListener;
}

void ArpEditBar::buttonClicked(Button* button)
{
	if (button == noteUpButton)
	{
		listener->onNoteUp();
	}
	else if (button == noteDownButton)
	{
		listener->onNoteDown();
	}
	else if (button == noteLeftButton)
	{
		listener->onNoteLeft();
	}
	else if (button == noteRightButton)
	{
		listener->onNoteRight();
	}
	else
	{
		for (int i=0; i<kNumArpButtons; i++)
		{
			if (button == arpButton[i])
			{
				listener->onArpSelectButton(i);
			}
		}
	}
}
