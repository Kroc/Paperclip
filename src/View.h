#ifndef __VIEW_H
#define __VIEW_H

#include "HEikon.h"
#include "Model.h"

// a polymorphic interface is used for Paperclip's application views (edtior /
// file-browser / search), that is an abstract class defines the common methods
// between all application views
//
class CPaperclipView
	: public CCoeControl,
	  public MCoeControlObserver
//==============================================================================
{
public:
	//--------------------------------------------------------------------------
	void ConstructL(const TRect& aRect, CPaperclipModel* aModel);
	void SetModel(CPaperclipModel* aModel){ iModel = aModel; }
    
    // in order to enable/disable menu items, AppUI will ask the applicaiton
	// view if a command is currently possible. the application view handles
    // this because it may have multiple internal controls (e.g. file-broswer).
    // for example you cannot cut or copy unless there is a text selection
	//
	// `virutal` is required here so that the specific application view's
	// method is called first (if present) instead of this default response
	//
    virtual TBool CanHandleCommand(TInt /*aCommand*/){ return EFalse; };

    // relevant commands from AppUI will be passed on to the view.
    // (*must* be implemented)
    virtual void HandleCommandL(TInt aCommand) = 0;

	// define the font-sizes (twips) for the zoom-levels
	enum TZoomLevel
	{
		EZoomLevel1 = 140,
		EZoomLevel2 = 160,
		EZoomLevel3 = 180,
		EZoomLevel4 = 220,

		EZoomLevelDefault = EZoomLevel3
	};
	virtual void ZoomL(TZoomLevel aZoomLevel){
		// the deault implementation just sets the member variable;
		// implementations in subclasses can do this too, or call
		// `CPaperclipView::ZoomL(...)` to use this code here
		iZoomLevel = aZoomLevel;
	};

	// CCoeControl::
	//
	// note that this is abstract, and can't be implemented at this level
	// because setting the control borders depends on what controls are
	// within the view
    //
	virtual void SetAdjacent(TInt aAdjacent) = 0;

    // CCoeControl::
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent) = 0;

	virtual TKeyResponse OfferKeyEventL(
        const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/
    ){
		return EKeyWasNotConsumed;
	};
	
	// MCoeControlObserver::
	virtual void HandleControlEventL(
        CCoeControl* aControl, TCoeEvent aEventType
    ) = 0;

protected:
	//--------------------------------------------------------------------------
	CPaperclipModel* iModel;
	TZoomLevel iZoomLevel;		// current zoom-level of view
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
    TBool CanHandleCommand(TInt aCommand);
    void HandleCommandL(TInt aCommand);

	void ZoomL(TZoomLevel aZoomLevel);

protected:
	//--------------------------------------------------------------------------
	// CCoeControl::
	void SetAdjacent(TInt aAdjacent);
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	// MCoeControlObserver::
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	
	// MEikEdwinObserver::
	void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);

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
    void HandleCommandL(TInt aCommand);

protected:
	//--------------------------------------------------------------------------
	// CCoeControl::
	void SetAdjacent(TInt aAdjacent);
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	// MCoeControlObserver::
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

private:
	//--------------------------------------------------------------------------
};

#endif