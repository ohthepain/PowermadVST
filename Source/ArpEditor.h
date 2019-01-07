//
//  ArpEditor.h
//  NewProject - VST3
//
//  Created by Paul Wilkinson on 1/7/19.
//

#ifndef ArpEditor_h
#define ArpEditor_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "ArpEditBar.h"

class Screen
{
public:
	//Screen(Rectangle<int>& rect);
	Screen(AudioProcessorEditor* parent) {}
	virtual ~Screen() {}
	
	virtual void SetRect(int x, int y, int w, int h);
	
protected:
	Rectangle<int> rect;
};

class ArpEditor : public Screen
, private ArpEditBar::Listener
{
public:
	//ArpEditor(Rectangle<int>& rect);
	ArpEditor(AudioProcessorEditor* parent);
	~ArpEditor();
	
	void paint(juce::Graphics& g);
	
	void SetRect(int x, int y, int w, int h) override;
	
	virtual void onNoteUp() override;
	virtual void onNoteDown() override;
	virtual void onNoteLeft() override;
	virtual void onNoteRight() override;
	virtual void onArpSelectButton(int buttonNum) override;
	
private:
	ArpEditBar* arpEditBar;
};

#endif /* ArpEditor_h */
