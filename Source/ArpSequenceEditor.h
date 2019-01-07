//
//  ArpSequenceEditor.h
//  NewProject
//
//  Created by Paul Wilkinson on 1/7/19.
//

#ifndef ArpSequenceEditor_h
#define ArpSequenceEditor_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "ControlGroup.h"

class ArpNoteEditor
 : public ControlGroup
{
public:
	ArpNoteEditor();
	virtual ~ArpNoteEditor();
	
	void SetRect(int x, int y, int w, int h) override;

	void SetNumNotes(int numNotes);
};

#endif /* ArpSequenceEditor_h */
