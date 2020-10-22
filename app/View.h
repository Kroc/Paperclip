#ifndef __VIEW_H
#define __VIEW_H

#include "Model.h"

#include <coecntrl.h>
#include <coeccntx.h>
#include <eikbordr.h>

class CPaperclipView
	: public CCoeControl,
	  public MCoeControlObserver
{
public:
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	void ConstructViewL();

	void SetModel(CPaperclipModel* aModel){ iModel=aModel; }

	// CCoeControl::
	void Draw(const TRect& aRect) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	// MCoeControlObserver::
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

protected:
	CPaperclipModel* iModel;
};

#endif