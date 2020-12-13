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
    
    // clipboard decorators:
    //
    // in order to enable/disable menu items, AppUI will ask the applicaiton
	// view if cut/copy/paste is currently possible. the application view
	// handles this because it all depends on what is selected in the view,
	// which may have multiple controls (e.g. file-broswer)
    //
	// these three methods below have default implementations, meaning that
	// an application view that does not implement its own versions of these
	// methods will use this code instead
	//
	// `virutal` is required here so that the specific application view's
	// method is called first (if present) instead of these generic ones
	//
    virtual TBool CanCut(){ return EFalse; };
    virtual TBool CanCopy(){ return EFalse; };
    virtual TBool CanPaste(){ return EFalse; };
    virtual TBool CanSelect(){ return EFalse; };

    // relevant commands from AppUI will be passed on to the view
    virtual void HandleCommandL(TInt aCommand) = 0;

	// CCoeControl::
	//
	// note that this is abstract, and can't be implemented at this level
	// because setting the control borders depends on what controls are
	// within the view
    //
	virtual void SetAdjacent(TInt aAdjacent) = 0;

    // CCoeControl::
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent) = 0;

	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType){
		return EKeyWasNotConsumed;
	};
	
	// MCoeControlObserver::
	virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType) = 0;

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
    void HandleCommandL(TInt aCommand);

    // clipboard decorators:
    //
    TBool CanCut();
    TBool CanCopy();
    TBool CanPaste();

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

	// clipboard decorators:
    //
	// default to the abstract implementation
	// -- returns EFalse automatically
    //TBool CanCut();
    //TBool CanCopy();
    //TBool CanPaste();

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
	CPaperclipModel *iModel;
};

#endif