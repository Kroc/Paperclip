#ifndef __VIEW_EDITOR_H
#define __VIEW_EDITOR_H

#include "View.h"
#include "Model.h"

#include <eikenv.h>
#include <eikgted.h>
#include <eikon.mbg>

class CPaperclipViewEditor
	: public CPaperclipView
{
public:
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	void ConstructViewL();
	
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }
	~CPaperclipViewEditor();

	// CCoeControl::
	void Draw(const TRect& /*aRect*/) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
	CEikGlobalTextEditor* iTextEditor;
};

#endif