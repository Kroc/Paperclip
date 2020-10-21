#ifndef __VIEW_FILES_H
#define __VIEW_FILES_H

#include "View.h"
#include "Model.h"

class CPaperclipViewFiles : public CPaperclipView
{
public:
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	void ConstructViewL();
	void SetModel(CPaperclipModel* aModel){ iModel=aModel; }

private:
	// CCoeControl::
	void Draw(const TRect& /*aRect*/) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
	CPaperclipModel *iModel;
};

#endif