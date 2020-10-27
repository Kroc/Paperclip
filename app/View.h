#ifndef __VIEW_H
#define __VIEW_H

#include "HEikon.h"
#include "Model.h"


class CPaperclipView
	: public CCoeControl,
	  public MCoeControlObserver
//==============================================================================
{
public:
	//--------------------------------------------------------------------------
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);

	void ConstructViewL();
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }

	// CCoeControl::
	void Draw(const TRect& aRect) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	// MCoeControlObserver::
	void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

protected:
	//--------------------------------------------------------------------------
	CPaperclipModel* iModel;
};


class CPaperclipViewEditor
	: public CPaperclipView,
	  public MEikEdwinObserver
//==============================================================================
{
public:
	//--------------------------------------------------------------------------
	~CPaperclipViewEditor();
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	
	void ConstructViewL();
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }

	// CCoeControl::
	void Draw(const TRect& /*aRect*/) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	// MCoeControlObserver::
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	
	// MEikEdwinObserver::
	virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);

private:
	//--------------------------------------------------------------------------
	CEikGlobalTextEditor* iTextEditor;
};


class CPaperclipViewFiles
	: public CPaperclipView
//==============================================================================
{
public:
	//--------------------------------------------------------------------------
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	
	void ConstructViewL();
	void SetModel(CPaperclipModel* aModel){ iModel=aModel; }

private:
	//--------------------------------------------------------------------------
	// CCoeControl::
	void Draw(const TRect& /*aRect*/) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

private:
	//--------------------------------------------------------------------------
	CPaperclipModel *iModel;
};

#endif