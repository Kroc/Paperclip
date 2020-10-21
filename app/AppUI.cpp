#include "AppUI.h"
#include "Document.h"

#include <eikbctrl.h>
#include <eikbordr.h>
#include <eikedwin.h>
#include <eikedwin.hrh>			// for the EEikEdwin* constants

CPaperclipAppUi::CPaperclipAppUi()
{
	__DECLARE_NAME(_S("CPaperclipAppUi"));
}

void CPaperclipAppUi::ConstructL()
{
	// EIKON: construct the UI elements defined in
	// the resource file (i.e. toolbar / toolband)
    BaseConstructL();

	// from the app-document, get a reference to the model (internal state),
	// we need to pass this onto the views so that they can access that state
	iModel=((CPaperclipDocument*)iDocument)->Model();
	
	//iAppViewEditor=new(ELeave) CPaperclipViewEditor;
	//iAppViewEditor->ConstructL(ClientRect(), iModel);
	//iAppViewFiles=new(ELeave) CPaperclipViewFiles;
	//iAppViewFiles->ConstructL(ClientRect(), iModel);

	////////////////////////////////////////////////////////////////////////////
	//CGraphicsDevice* device=iCoeEnv->ScreenDevice();
	//iAppZoom.SetGraphicsDeviceMap(device);
	//iAppZoom.SetZoomFactor(EZoomOneToOne);
	
	iTextEditor=new(ELeave) CEikGlobalTextEditor(TEikBorder::ESingleBlack);

	const TInt edwin_flags=0
		| EEikEdwinOwnsWindow
		| EEikEdwinKeepDocument
		| EEikEdwinInclusiveSizeFixed
		| EEikEdwinUserSuppliedText
		| EEikEdwinNoAutoSelection
		| EEikEdwinAlwaysShowSelection
	;
	iTextEditor->ConstructL(
		NULL,0,0,edwin_flags,
		EEikFontControlSize,
		EEikMonospaceFontsOnly
	);
	//iTextEditor->SetObserver(this);
	//iTextEditor->SetEdwinObserver(this);
	iTextEditor->CreateScrollBarFrameL();
	iTextEditor->ScrollBarFrame()->SetScrollBarVisibilityL(
		CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto
	);
	iTextEditor->SetAdjacent(ECoeAdjTop|ECoeAdjRight);
	//iTextEditor->SetZoomFactorL(&iAppZoom);
	iTextEditor->SetDocumentContentL(*iModel->GlobalText(), CEikEdwin::EUseText);
	iTextEditor->SetRectL(ClientRect());
	iTextEditor->ActivateL();

	////////////////////////////////////////////////////////////////////////////
	// begin with the editor view
	// (the default when opening the application)
	//iAppViewFiles->MakeVisible(EFalse);
	
	// EIKON: the application view must be on the control stack
	// so that it can receive key press events
	//iAppView=iAppViewEditor;
	//AddToStackL(iAppView);
	
	// Create the toolbands for the two views.
	// The EIKON framework creates the "circle" toolband when the 
	// application is started, because it is listed in the 
	// EIK_APP_INFO resource in the resource file. Therefore we
	// don't need to create it again. The App UI stores a pointer
	// to it in iToolBand, so save this as iCircleToolBand.
	// Then, create another toolband for the "square" view.
	// This means we've got a pointer to both toolbands.
	iCircleToolBand=iToolBand;
	iSquareToolBand=new (ELeave) CEikToolBar;
	// Zero iToolBand, otherwise ClientRect() passed to ConstructL() will be wrong
	iToolBand=0;
	iSquareToolBand->ConstructL(this, R_EXAMPLE_SQUARE_TOOLBAND, ClientRect());
	iSquareToolBand->MakeVisible(EFalse);
	// Set iToolBand back so that the "circle" toolband is 
	// displayed at the beginning.
	iToolBand=iCircleToolBand;

	// display application name on toolbar
	CEikFileNameLabel* filenameLabel=(CEikFileNameLabel*) iToolBar->ControlById(EPaperclipCmdProjectName);
	filenameLabel->UpdateL();

	// make the toolbar reflect the selected view
	UpdateToolbarL();
}

CPaperclipAppUi::~CPaperclipAppUi()
{
	delete iTextEditor;

	delete iAppViewEditor;
    delete iAppViewFiles;

	// Whichever toolband was active when the app was closed down will
	// already have been deleted, because the framework deletes iToolBand.
	// If we set iToolBand to 0, deleting it again will not cause
	// an error.
	iToolBand=0;
	delete iCircleToolBand;
	delete iSquareToolBand;
}

void CPaperclipAppUi::HandleCommandL(
	TInt aCommand
){
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
{
	// don't change to self
	if (iViewType==EViewEditor) return;
	
	// set the member variable
	iViewType=EViewEditor;

	// deconstruct the current view
	RemoveFromStack(iAppView);
	iAppView->MakeVisible(EFalse);
	
	// switch to the editor view
	iAppView=iAppViewEditor;
	iAppView->MakeVisible(ETrue);
	AddToStackL(iAppView);
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

void CPaperclipAppUi::CmdSetViewFilesL()
{
	// don't change to self
	if (iViewType==EViewFiles) return;
	
	// set the member variable
	iViewType=EViewFiles;

	// deconstruct the current view
	RemoveFromStack(iAppView);
	iAppView->MakeVisible(EFalse);
	
	// switch to the files view
	iAppView=iAppViewFiles;
	iAppView->MakeVisible(ETrue);
	AddToStackL(iAppView);
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
{
	CEikButtonBase* button;
	
	button=STATIC_CAST(CEikButtonBase*, iToolBar->ControlById(EPaperclipCmdEditorView));
	button->SetState((iViewType == EViewEditor) ? CEikButtonBase::ESet : CEikButtonBase::EClear);
	button->DrawNow();

	button=STATIC_CAST(CEikButtonBase*, iToolBar->ControlById(EPaperclipCmdFilesView));
	button->SetState((iViewType == EViewFiles) ? CEikButtonBase::ESet : CEikButtonBase::EClear);
	button->DrawNow();
}

void CPaperclipAppUi::CmdViewSelectionPopoutL()
{
	// Calculate the position to display the popup menu.
	TPoint point(iToolBar->Position()+iToolBar->ControlById(EPaperclipCmdEditorView)->Position());
	// Launch the popup menu. In this example, we use the same menu pane as the 
	// cascaded Switch View menu.
	LaunchPopupMenuL(R_EXAMPLE_SWITCHVIEW_MENU, point, EPopupTargetBottomRight);
	CEikButtonBase* viewButton=STATIC_CAST(CEikButtonBase*, iToolBar->ControlById(EPaperclipCmdEditorView));
	CEikMenuPane* popup=Popup();
	popup->SetLaunchingButton(viewButton);	// These two lines cause the View button to
	viewButton->SetIgnoreNextPointerUp();	// latch until the popup menu is dismissed.
	popup->ClaimPointerGrab();	// The popup menu needs to grab the pointer so that it
								// can move the highlight between the menu items, and
								// also so that it disappears when the user lifts 
								// the pointer outside the menu.
}

void CPaperclipAppUi::DynInitMenuPaneL(
	TInt aMenuId,
	CEikMenuPane* aMenuPane
){
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