#include "View.h"

void CPaperclipView::Draw(
	const TRect& aRect
) const
{}

void CPaperclipView::HandleControlEventL(
	CCoeControl* aControl,
	TCoeEvent aEventType
){}

void CPaperclipView::HandlePointerEventL(
	const TPointerEvent &aPointerEvent
){}

TKeyResponse CPaperclipView::OfferKeyEventL(
	const TKeyEvent& aKeyEvent,
	TEventCode aType
){
	return EKeyWasNotConsumed;
}