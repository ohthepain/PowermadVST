//
//  ArpEditBar.h
//  NewProject - VST3
//
//  Created by Paul Wilkinson on 1/7/19.
//

#ifndef ArpEditBar_h
#define ArpEditBar_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "ControlGroup.h"

class ArpEditBar : public ControlGroup
, private Button::Listener
{
public:
	class Listener
	{
	protected:
		virtual ~Listener() {}
	public:
		virtual void onNoteUp() = 0;
		virtual void onNoteDown() = 0;
		virtual void onNoteLeft() = 0;
		virtual void onNoteRight() = 0;
		virtual void onArpSelectButton(int buttonNum) = 0;
	};
	
public:
	ArpEditBar(AudioProcessorEditor* parent);
	~ArpEditBar();
	
	void SetRect(int x, int y, int w, int h) override;
	void SetListener(ArpEditBar::Listener* listener);
	void buttonClicked (Button*) override;
	
private:
	//bstatic const int kHeight = 40;
	static const int kArrowButtonWidth = 40;
	static const int kTextButtonWidth = 80;
	static const int kNumArpButtons = 4;
	
	ArpEditBar::Listener* listener;
	
	Button* noteUpButton;
	Button* noteDownButton;
	Button** arpButton;
	Button* noteLeftButton;
	Button* noteRightButton;
};

#endif /* ArpEditBar_h */
