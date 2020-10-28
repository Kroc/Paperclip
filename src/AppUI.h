#ifndef __APPUI_H
#define __APPUI_H

#include "HApp.h"

#include "HPaperclip.h"

#include "ViewEditor.h"
#include "ViewFiles.h"

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
	enum TViewType {
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
	CCoeControl* iAppView;
	
	CEikToolBar* iCircleToolBand;
	CEikToolBar* iSquareToolBand;

	CPaperclipModel *iModel;

	CEikGlobalTextEditor* iTextEditor;
};

#endif