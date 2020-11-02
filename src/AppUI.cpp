#include "AppUI.h"
#include "Document.h"

#include "HEikon.h"


CPaperclipAppUi::CPaperclipAppUi()
//==============================================================================
{
	__DECLARE_NAME(_S("CPaperclipAppUi"));
}

void CPaperclipAppUi::ConstructL()
//==============================================================================
{
	// toolbar / toolband:
	////////////////////////////////////////////////////////////////////////////
	// EIKON: construct the UI elements defined in
	// the resource file (i.e. toolbar / toolband)
    BaseConstructL();

	// the resource file will build the empty toolbar to begin with
	iToolBarType = EToolBarEmpty;

	// toolband functionality is incomplete,
	// so hide from release builds
	//
#ifdef _DEBUG

	// an interesting bug/feature of EIKON is that when both a default toolbar
	// and toolband are defined in the resource file, they will overlap each
	// other in the top-right corner. the Word source code uses this to provide
	// the "filename label" (task switched) on BOTH the toolbar & toolband, so
	// that when on or the other are hidden, a filenmae label remains in the
	// top-right corner _without_ having to do any runtime manipulation!
	//
	// if we change toolbands (or don't have one defined by default), then this
	// overlap will not happen as the toolbar is already occupying that space.
	// whilst we could manually manipulate the toolband's Rect to do what we
	// want, it's easier to simply hide the toolbar whilst we construct the
	// the toolband to achieve the same effect
	//
	iToolBar->MakeVisible( EFalse );

	// create the toolband for the editor view
	iEditorToolBand = new( ELeave ) CEikToolBar; 
	iEditorToolBand->ConstructL(
		this, R_PAPERCLIP_EDITOR_TOOLBAND, ClientRect()
	);
	//TODO: the size/position of the views depends upon there being a toolband
	//		present, at the moment we keep one visible whilst the views are
	//		constructed, but it would be better to position the view correctly
	//		without the toolband having to be present yet
	//		
//	iEditorToolBand->MakeVisible( EFalse );
	iToolBand = iEditorToolBand;

	iToolBar->MakeVisible( ETrue );

#endif
	// views:
	////////////////////////////////////////////////////////////////////////////
	// from the app-document, get a reference to the model (internal state),
	// we need to pass this onto the views so that they can access that state
	iModel = ((CPaperclipDocument*) iDocument)->Model();
	
	iAppViewEditor = new(ELeave) CPaperclipViewEditor;
	iAppViewEditor->ConstructL( ClientRect(), iModel );
	iAppViewEditor->MakeVisible( EFalse );

	iAppViewFiles = new(ELeave) CPaperclipViewFiles;
	iAppViewFiles->ConstructL( ClientRect(), iModel );
	iAppViewFiles->MakeVisible( EFalse );

	iViewType = EViewNone;
	CmdSetViewEditorL();

	// update application name on toolbar / toolband
	UpdateFileNameLabelL();
}


CPaperclipAppUi::~CPaperclipAppUi()
//==============================================================================
{
	delete iAppViewEditor;
    delete iAppViewFiles;

	// whichever toolband was active when the app was closed down will
	// already have been deleted, because the framework deletes iToolBand.
	// if we set iToolBand to 0, deleting it again will not cause an error
	iToolBand = 0;
	delete iEditorToolBand;
}

// the "file name label" is the task-switcher in the top-right of the screen
// provided by EIKON. in this case, the "file name" is not the current text-
// file being edited, but rather the Project file for this app instance
//
void CPaperclipAppUi::UpdateFileNameLabelL()
//==============================================================================
{
	CEikFileNameLabel* label;
	
	label = STATIC_CAST( CEikFileNameLabel*,
		iToolBar->ControlById( EPaperclipCmdProjectName )
	);
	label->UpdateL();
	label->DrawNow();

	// incomplete toolband not present in release builds
#ifdef _DEBUG

	if (iToolBand){
		label = STATIC_CAST( CEikFileNameLabel*,
			iToolBand->ControlById( EPaperclipCmdProjectName )
		);
		label->UpdateL();
		label->DrawNow();
	};

#endif
}

void CPaperclipAppUi::HandleCommandL(
	TInt aCommand
)
//==============================================================================
{
	switch (aCommand)
	{
	// "Editor" button on the toolbar,
	// to switch to the text-editor view
    case EPaperclipCmdEditorView:
        CmdSetViewEditorL();
        break;

	// "Files" button on the toolbar,
	// to switch to the file-browser view
    case EPaperclipCmdFilesView:
        CmdSetViewFilesL();
        break;

	// Exit the application
	case EEikCmdExit: 
		Exit();
		break;
	}
}

void CPaperclipAppUi::CmdSetViewEditorL()
//==============================================================================
{
	// don't change to self
	if (iViewType == EViewEditor) return;
	// whilst making the change, treat as no view
	iViewType = EViewNone;

	if (iAppView){
		// stop events going to the view by removing it from the stack
		RemoveFromStack( iAppView );
		// hide the current view (but keep it loaded)
		iAppView->MakeVisible( EFalse );
	};
		
	// switch to the editor view
	iAppView = iAppViewEditor;
	iAppView->MakeVisible( ETrue );
	AddToStackL( iAppView );
	iAppView->DrawNow();

#ifdef _DEBUG

	if (iToolBand) iToolBand->MakeVisible( EFalse );
	iToolBand = iEditorToolBand;
	iToolBand->MakeVisible( ETrue );
	iToolBand->DrawNow();

//	// switch menubar and hotkeys
//	MenuBar()->ChangeMenuBarL(R_PAPERCLIP_HOTKEYS,R_EXAMPLE_MENUBAR_CIRCLE,EFalse);
	iAppView->SetAdjacent( ECoeAdjTop | ECoeAdjRight );
#else
	iAppView->SetAdjacent( ECoeAdjRight );
#endif

	// remember currently selected view
	iViewType = EViewEditor;
	// set the selected button on the toolbar
	UpdateToolbarL();
}

void CPaperclipAppUi::CmdSetViewFilesL()
//==============================================================================
{
	// don't change to self
	if (iViewType == EViewFiles) return;
	
	// set the member variable
	iViewType = EViewFiles;

	// stop events going to the view by removing it from the stack
	RemoveFromStack( iAppView );
	// hide the current view (but keep it loaded)
	iAppView->MakeVisible( EFalse );
	
	// switch to the files view
	iAppView = iAppViewFiles;
	iAppView->MakeVisible( ETrue );
	AddToStackL( iAppView );
	iAppView->DrawNow();

	// set the selected button on the toolbar
	UpdateToolbarL();

/*	// Switch toolband
	iToolBand->MakeVisible(EFalse);
	iToolBand=iCircleToolBand;
	iToolBand->MakeVisible(ETrue);
	iToolBand->DrawNow();
	// switch menubar and hotkeys
	MenuBar()->ChangeMenuBarL(R_PAPERCLIP_HOTKEYS,R_EXAMPLE_MENUBAR_CIRCLE,EFalse);
*/
}

void CPaperclipAppUi::UpdateToolbarL()
//==============================================================================
{
	// nothing to update on the empty toolbar
	if (iToolBarType == EToolBarEmpty) return;

	CEikButtonBase* button;
	
	button = STATIC_CAST( CEikButtonBase*,
		iToolBar->ControlById( EPaperclipCmdEditorView )
	);
	button->SetState(
		(iViewType == EViewEditor)
		? CEikButtonBase::ESet
		: CEikButtonBase::EClear
	);
	button->DrawNow();

	button = STATIC_CAST( CEikButtonBase*,
		iToolBar->ControlById( EPaperclipCmdFilesView )
	);
	button->SetState(
		(iViewType == EViewFiles)
		? CEikButtonBase::ESet
		: CEikButtonBase::EClear
	);
	button->DrawNow();
}

/*
void CPaperclipAppUi::CmdViewSelectionPopoutL()
//==============================================================================
{
	// Calculate the position to display the popup menu.
	TPoint point(
		iToolBar->Position() +
		iToolBar->ControlById( EPaperclipCmdEditorView )->Position()
	);
	// launch the popup menu:
	// in this example, we use the same menu
	// pane as the cascaded Switch View menu
	LaunchPopupMenuL(
		R_EXAMPLE_SWITCHVIEW_MENU,
		point, EPopupTargetBottomRight
	);
	CEikButtonBase* viewButton = STATIC_CAST( CEikButtonBase*,
		iToolBar->ControlById( EPaperclipCmdEditorView )
	);
	CEikMenuPane* popup = Popup();
	// these two lines cause the View button to
	// latch until the popup menu is dismissed
	popup->SetLaunchingButton(viewButton);
	viewButton->SetIgnoreNextPointerUp();
	// the popup menu needs to grab the pointer so that it can move the
	// highlight between the menu items, and also so that it disappears
	// when the user lifts the pointer outside the menu
	popup->ClaimPointerGrab();
}
*/

void CPaperclipAppUi::DynInitMenuPaneL(
	TInt aMenuId,
	CEikMenuPane* aMenuPane
)
//==============================================================================
{
/*	if (aMenuId==R_EXAMPLE_SWITCHVIEW_MENU)
	{
		// Set the state of the radio button symbol to reflect which view is
		// currently active.
		if (iViewType==EViewCircle)
			aMenuPane->SetItemButtonState(EExampleCmdSwitchToCircleView,EEikMenuItemSymbolOn);
		else
			aMenuPane->SetItemButtonState(EExampleCmdSwitchToSquareView,EEikMenuItemSymbolOn);
	}
*/
}

void CPaperclipAppUi::HandleControlEventL(
	CCoeControl* aControl,
	TCoeEvent aEventType
)
//==============================================================================
{}


// when the application receives a key-press,
// we need to pass that on to the current view
//
void CPaperclipAppUi::HandleKeyEventL(
	const TKeyEvent& aKeyEvent,
	TEventCode aType
)
//==============================================================================
{
	this->iAppView->OfferKeyEventL( aKeyEvent, aType );
}
