#include "ViewEditor.h"
#include <eikedwin.hrh>			// for the EEikEdwin* constants

CPaperclipViewEditor::~CPaperclipViewEditor()
{
}

void CPaperclipViewEditor::ConstructL(
	const TRect& aRect,
	CPaperclipModel* aModel
){
	iModel=aModel;

    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
    SetRectL(aRect);
    ActivateL();
}

// TODO: ultimately, we probably want to just draw the view
// from an already-composited off-screen buffer to save CPU
// (invalidation may fire multiple times in a row) and also
// because this method CANNOT 'Leave'
//
void CPaperclipViewEditor::Draw(
	const TRect& //aRect
)	const
{
	CWindowGc& gc = SystemGc();
	gc.Clear();

	//TRect drawRect=Rect();
	//gc.DrawRect(drawRect);
}

void CPaperclipViewEditor::HandlePointerEventL(
	const TPointerEvent& //aPointerEvent
){
	DrawNow();
}
