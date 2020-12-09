#include "View.h"

void CPaperclipViewFiles::ConstructL(
    const TRect& aRect,
    CPaperclipModel* aModel
){
    iModel = aModel;
    
    CreateWindowL();
    Window().SetShadowDisabled( ETrue );
    SetRectL( aRect );
    ActivateL();
}

void CPaperclipViewFiles::SetAdjacent(
    TInt aAdjacent
){
}

void CPaperclipViewFiles::HandleControlEventL(
    CCoeControl* aControl,
    TCoeEvent aEventType
){
}

void CPaperclipViewFiles::HandlePointerEventL(
    const TPointerEvent& //aPointerEvent
){
    DrawNow();
}

TKeyResponse CPaperclipViewFiles::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType
){
    return EKeyWasNotConsumed;
}

//TBool CPaperclipViewFiles::CanCut(){};
//TBool CPaperclipViewFiles::CanCopy(){};
//TBool CPaperclipViewFiles::CanPaste(){};

void CPaperclipViewFiles::DoCutL(){};
void CPaperclipViewFiles::DoCopyL(){};
void CPaperclipViewFiles::DoPasteL(){};