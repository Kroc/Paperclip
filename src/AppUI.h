#ifndef __APPUI_H
#define __APPUI_H

#include "HApp.h"
#include "HPaperclip.h"
#include "View.h"


class CPaperclipAppUi
	: public CEikAppUi,
	  public MCoeControlObserver
{
public:
	//--------------------------------------------------------------------------
	CPaperclipAppUi();			// constructor
	~CPaperclipAppUi();			// destructor

	// CEikAppUi::
    void ConstructL();

private:
	//--------------------------------------------------------------------------
	// CPaperclipAppUi::
	void UpdateFileNameLabelL();

	void CmdSetViewEditorL();
	void CmdSetViewFilesL();

	// make the buttons on the toolbar (right-side)
	// reflect the currently selected view
	void UpdateToolbarL();

	void CmdViewSelectionPopoutL();

private:
	//--------------------------------------------------------------------------
	// CEikAppUi::
	void HandleCommandL(TInt aCommand);
	// CCoeAppUi::
	void HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	// MEikMenuObserver::
	void DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane);
	// MCoeControlObserver::
	virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

private:
	//--------------------------------------------------------------------------
	// which toolbar is in use
	enum TToolBarType {
		// empty toolbar with no app-specific buttons
		// (just filename-label and clock)
		EToolBarEmpty,
		// the toolbar used when a project is open,
		// providing buttons to change mode
		EToolBarMain
	};
	TToolBarType iToolBarType;
	
	enum TViewType {
		EViewNone,
		EViewEditor,
		EViewFiles,
		EViewSearch,
		EViewConfig
	};
	TViewType iViewType;

	// application views:
	CPaperclipViewEditor* iAppViewEditor;
    CPaperclipViewFiles*  iAppViewFiles;
	// (currently selected view)
	CPaperclipView* iAppView;
	
	CEikToolBar* iEditorToolBand;

	CPaperclipModel *iModel;
};

#endif