#ifndef __VIEW_H
#define __VIEW_H

#include <coecntrl.h>
#include <coeccntx.h>

#include "Model.h"

class CPaperclipView
	: public CCoeControl,
	  public MCoeControlObserver
{
public:
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	void ConstructViewL();
	void SetModel(CPaperclipModel* aModel){ iModel=aModel; }

private:
	// CCoeControl::
	void Draw(const TRect& aRect) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	// MCoeControlObserver::
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

protected:
	CPaperclipModel *iModel;
};

#endif