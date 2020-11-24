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
    
    // TODO: we will need to recreate this cursor whenever we zoom,
    //       does it need to be stored in the class?
    CFbsBitmap* line_cursor = iEikonEnv->CreateBitmapL(
        TPtrC(), EMbmEikonLncusr1
    );
    CleanupStack::PushL( line_cursor );
    iTextEditor->SetLineCursorBitmapL( line_cursor );
    CleanupStack::Pop();

    iTextEditor->SetRectL( Rect() );
    iTextEditor->ActivateL();
    
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

// TODO: ultimately, we probably want to just draw the view
// from an already-composited off-screen buffer to save CPU
// (invalidation may fire multiple times in a row) and also
// because this method CANNOT 'Leave'
//
void CPaperclipViewEditor::Draw(
    const TRect& //aRect
)   const
{/*
    CWindowGc& gc = SystemGc();
    gc.Clear();
    
    //TRect drawRect=Rect();
    //gc.DrawRect(drawRect);
*/}

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
