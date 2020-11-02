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
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }

	// CCoeControl::
	//
	// note that this is abstract, and can't be implemented at this level
	// because setting the control borders depends on what controls are
	// within the view
	virtual void SetAdjacent(TInt aAdjacent){};

	void Draw(const TRect& aRect) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);

	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType){
		return EKeyWasNotConsumed;
	};
	
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
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }

	// CCoeControl::
	virtual void SetAdjacent(TInt aAdjacent);
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
	void SetModel(CPaperclipModel* aModel){ iModel=aModel; }

private:
	//--------------------------------------------------------------------------
	// CCoeControl::
	virtual void SetAdjacent(TInt aAdjacent);
	void Draw(const TRect& /*aRect*/) const;
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

private:
	//--------------------------------------------------------------------------
	CPaperclipModel *iModel;
};

#endif