#ifndef __APPUI_H
#define __APPUI_H

// enums:
#include <eikcmds.hrh>			// EEikCmdExit &c.
#include <eikmenu.hrh>			// menu-items

#include <eikappui.h>			// CEikAppUi
#include <eiktbar.h>			// toolbar/band
#include <eikbutb.h>			// buttons
#include <eikfnlab.h>			// file-name label
#include <eikmenub.h>			// menu-bar
#include <eikedwin.h>			// text editor
#include <eikgted.h>

#include "Paperclip.h"
#include "ViewEditor.h"
#include "ViewFiles.h"

class CPaperclipAppUi : public CEikAppUi
{
public:
	// CEikAppUi:
	CPaperclipAppUi();			// constructor
	~CPaperclipAppUi();			// destructor
    void ConstructL();

private:
	// CEikAppUi:
	void HandleCommandL(TInt aCommand);
	
	// CPaperclipAppUi:
	//
	void CmdSetViewEditorL();
	void CmdSetViewFilesL();

	// make the buttons on the toolbar (right-side)
	// reflect the currently selected view
	void UpdateToolbarL();

	void CmdViewSelectionPopoutL();

private:
	// MEikMenuObserver:
	void DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane);

private:
	// view type
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
	
	// Toolband
	CEikToolBar* iCircleToolBand;
	CEikToolBar* iSquareToolBand;

	// Model
	CPaperclipModel *iModel;

	CEikGlobalTextEditor* iTextEditor;
};

#endif