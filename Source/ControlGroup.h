//
//  ControlGroup.h
//  NewProject - VST3
//
//  Created by Paul Wilkinson on 1/7/19.
//

#ifndef ControlGroup_h
#define ControlGroup_h

#include "../JuceLibraryCode/JuceHeader.h"

class ControlGroup
{
public:
	//ControlGroup(const Rectangle<int>& rect);
	ControlGroup() {}
	virtual ~ControlGroup() {}
	
	virtual void SetRect(int x, int y, int w, int h) {}
	
private:
	Rectangle<int> rect;
};

#endif /* ControlGroup_h */
