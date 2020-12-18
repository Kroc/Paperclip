#include "View.h"

void CPaperclipViewEditor::ConstructL(
    const TRect& aRect,
    CPaperclipModel* aModel
)
//==============================================================================
{
    iModel = aModel;
    
    this->CreateWindowL();
    this->Window().SetShadowDisabled( ETrue );
    this->Window().SetBackgroundColor();
    this->SetRectL( aRect );
    this->SetBlank();
    this->ActivateL();
    
    iTextEditor = new( ELeave ) CEikGlobalTextEditor(
        TEikBorder::ESingleBlack
    );
    
    const TInt edwin_flags = 0
        | EEikEdwinOwnsWindow
        | EEikEdwinKeepDocument
        | EEikEdwinInclusiveSizeFixed
        | EEikEdwinUserSuppliedText
        | EEikEdwinNoAutoSelection
        | EEikEdwinAlwaysShowSelection
    ;
    iTextEditor->ConstructL(
        this, 0, 0, edwin_flags,
        EEikFontControlSize,
        EEikMonospaceFontsOnly
    );
    iTextEditor->SetObserver( this );
    iTextEditor->SetEdwinObserver( this );
    
    iTextEditor->CreateScrollBarFrameL();
    iTextEditor->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff,
        CEikScrollBarFrame::EAuto
    );
    iTextEditor->SetDocumentContentL(
        *iModel->GlobalText(),
        CEikEdwin::EUseText
    );

    iTextEditor->SetRectL( Rect() );
    iTextEditor->ActivateL();

	// set beginning zoom-level:
	ZoomL( EZoomLevelDefault );

    iTextEditor->SetFocus( ETrue );
}

CPaperclipViewEditor::~CPaperclipViewEditor()
//==============================================================================
{
    delete iTextEditor;
}

void CPaperclipViewEditor::SetAdjacent(
    TInt aAdjacent
)
//==============================================================================
{
    // the editor view has only one control (the text-editor), for now
    iTextEditor->SetAdjacent( aAdjacent );
}

void CPaperclipViewEditor::HandlePointerEventL(
    const TPointerEvent& //aPointerEvent
){/*
    DrawNow();
*/}

void CPaperclipViewEditor::HandleControlEventL(
    CCoeControl* aControl,
    TCoeEvent aEventType
){
}

void CPaperclipViewEditor::HandleEdwinEventL(
    CEikEdwin* aEdwin,
    TEdwinEvent aEventType
){/*
    if (aEdwin==iRichEd && (aEventType==MEikEdwinObserver::EEventFormatChanged || 
                            aEventType==MEikEdwinObserver::EEventNavigation))
    {
        if (aEventType==MEikEdwinObserver::EEventFormatChanged)
        {
            SetPaginationOutOfDate(ETrue);
            SetDocChanged();
        }
        if (iToolBar->IsVisible() || iToolBand->IsVisible())
            iToolBarUpdate->Start(CWordToolBarUpdate::EFullUpdate)
        ;
    }
*/}

TKeyResponse CPaperclipViewEditor::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType
)
//==============================================================================
{
    return iTextEditor->OfferKeyEventL( aKeyEvent, aType );
}

TBool CPaperclipViewEditor::CanHandleCommand(
    TInt aCommand
)
//==============================================================================
{
    switch (aCommand){
    case EEikCmdEditCut:
    case EEikCmdEditCopy:
        // cutting/copying is only possible if there's a selection
        return (iTextEditor->Selection().Length() > 0);
        break;

    case EEikCmdEditPaste:
        // nothing prevents pasting, yet
        // TODO: cannot paste if clipboard is empty!
        return ETrue;
        break;
	}
    return EFalse;
}

void CPaperclipViewEditor::HandleCommandL(
    TInt aCommand
)
//==============================================================================
{
    switch (aCommand){
	case EEikCmdEditCut:
	    iTextEditor->ClipboardL( CEikEdwin::ECut );
	    break;
	
	case EEikCmdEditCopy:
	    iTextEditor->ClipboardL( CEikEdwin::ECopy );
	    break;
	
	case EEikCmdEditPaste:
	    iTextEditor->ClipboardL( CEikEdwin::EPaste );
	    break;
	
	case EEikCmdEditSelectAll:
	    // this can Leave! possibly because of
	    // some selection meta-data being allocated
	    iTextEditor->SelectAllL();
	    break;
	
	// sidebar zoom buttons
	//
	case EEikCmdZoomIn:
		switch (iZoomLevel){
		case EZoomLevel1: ZoomL( EZoomLevel2 ); break;
		case EZoomLevel2: ZoomL( EZoomLevel3 ); break;
		case EZoomLevel3: ZoomL( EZoomLevel4 ); break;
		case EZoomLevel4: ZoomL( EZoomLevel1 ); break;
		default: ZoomL( EZoomLevelDefault );
		}
		break;

	case EEikCmdZoomOut:
		switch (iZoomLevel){
		case EZoomLevel1: ZoomL( EZoomLevel4 ); break;
		case EZoomLevel2: ZoomL( EZoomLevel1 ); break;
		case EZoomLevel3: ZoomL( EZoomLevel2 ); break;
		case EZoomLevel4: ZoomL( EZoomLevel3 ); break;
		default: ZoomL( EZoomLevelDefault );
		}
		break;
    }
}

// apply a zoom-level to the view
//
void CPaperclipViewEditor::ZoomL(
	TZoomLevel aZoomLevel
)
//==============================================================================
{
	// create a character format to describe the new font-size
	TCharFormat charFormat;
	charFormat.iFontSpec.iHeight = aZoomLevel;
	// set the mask bit to change only font-size
	TCharFormatMask charFormatMask;
	charFormatMask.SetAttrib( EAttFontHeight );
	// apply the format change to the text-editor
	// (`CGlobalText` uses one format for all text)
	iTextEditor->ApplyCharFormatL( charFormat, charFormatMask );

	// set the bitmap for the line-cursor:
	//
	TInt bitmap_id = EMbmEikonLncusr1;
	switch (aZoomLevel)
	{
	case EZoomLevel1:
	case EZoomLevel2:
		bitmap_id = EMbmEikonLncusr1;
		break;
	case EZoomLevel3:
		bitmap_id = EMbmEikonLncusr3;
		break;
	case EZoomLevel4:
		bitmap_id = EMbmEikonLncusr4;
		break;
	}
	CFbsBitmap* lineCursor = iEikonEnv->CreateBitmapL( TPtrC(), bitmap_id );
	CleanupStack::PushL( lineCursor );
	iTextEditor->SetLineCursorBitmapL( lineCursor );
	CleanupStack::Pop();

	// call the super-class implementation;
	// this just sets the member variable, iZoomLevel
	CPaperclipView::ZoomL( aZoomLevel );

	iTextEditor->DrawNow();
}
