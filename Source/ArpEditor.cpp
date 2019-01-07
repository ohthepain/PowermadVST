//
//  ArpEditor.cpp
//  NewProject - VST3
//
//  Created by Paul Wilkinson on 1/7/19.
//

#include "ArpEditor.h"

void Screen::SetRect(int x, int y, int w, int h)
{
	rect.setX(x);
	rect.setY(y);
	rect.setWidth(w);
	rect.setHeight(h);
}

ArpEditor::ArpEditor(AudioProcessorEditor* parent)
: Screen(parent)
{
	arpEditBar = new ArpEditBar(parent);
	arpEditBar->SetListener(this);
}

ArpEditor::~ArpEditor()
{
	delete arpEditBar;
	arpEditBar = nullptr;
}

void ArpEditor::SetRect(int x, int y, int w, int h)
{
	Screen::SetRect(x, y, w, h);
	//x = 0;
	y = 40;
	//int w = rect.getWidth();
	h = 30;
	arpEditBar->SetRect(x, rect.getY() + 6, w, h);
}

void ArpEditor::onNoteUp()
{
	
}

void ArpEditor::onNoteDown()
{
	
}
void ArpEditor::onNoteLeft()
{
	
}
void ArpEditor::onNoteRight()
{
	
}
void ArpEditor::onArpSelectButton(int buttonNum)
{
	
}

void ArpEditor::paint(juce::Graphics& g)
{
	g.setColour (Colours::white);
	g.setFont (15.0f);
	//g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	
	Point<float> topLeft((float)rect.getX(), (float)rect.getY() + 1);
	Point<float> bottomLeft((float)rect.getX(), (float)rect.getBottom());
	Point<float> topRight((float)rect.getRight(), (float)rect.getY() + 1);
	Point<float> bottomRight((float)rect.getRight(), (float)rect.getBottom());
	
	float lineThickness = 3.0f;
	g.setColour (Colours::darkgrey);
	g.drawLine (Line<float>(topLeft, topRight), lineThickness);
	g.drawLine (Line<float>(topLeft, bottomLeft), lineThickness);
	g.setColour (Colours::lightgrey);
	g.drawLine (Line<float>(bottomLeft, bottomRight), lineThickness);
	g.drawLine (Line<float>(topRight, bottomRight), lineThickness);
}
