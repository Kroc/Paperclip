// model (internal state) for the application:
//
#include "Model.h"

CPaperclipModel::CPaperclipModel()
{
	__DECLARE_NAME(_S("CPaperclipModel"));
}

// static instantiation:
//
CPaperclipModel* CPaperclipModel::NewL()
{
	CPaperclipModel* self=new(ELeave) CPaperclipModel();
	CleanupStack::PushL(self);

	self->ConstructL();
	
	CleanupStack::Pop();  // self
	return self;
}

void CPaperclipModel::ConstructL()
{
	// Create a default usable Normal style (the default layers)
	CParaFormat		paraFormat;
	TParaFormatMask paraFormatMask;
	paraFormat.iSpaceAfterInTwips=100;
	paraFormatMask.SetAttrib(EAttSpaceAfter);
	paraFormat.iHorizontalAlignment=CParaFormat::ELeftAlign;
	paraFormatMask.SetAttrib(EAttAlignment);
	iParaFormatLayer=CParaFormatLayer::NewL(&paraFormat,paraFormatMask);
	//
	TCharFormat		charFormat;
	TCharFormatMask charFormatMask;
	TInt typefaceAttributes = TTypeface::EProportional | TTypeface::ESerif;
	charFormat.iFontSpec.iTypeface.SetAttributes(typefaceAttributes);
	charFormat.iFontSpec.iHeight = 200;
	charFormatMask.SetAttrib(EAttFontTypeface);
	charFormatMask.SetAttrib(EAttFontHeight);
	iCharFormatLayer=CCharFormatLayer::NewL(charFormat,charFormatMask);

	iGlobalText = CGlobalText::NewL(
		iParaFormatLayer,
		iCharFormatLayer,
		CEditableText::ESegmentedStorage,
		CEditableText::EDefaultTextGranularity
	);
}

CPaperclipModel::~CPaperclipModel()
{
	delete iCharFormatLayer;
	delete iParaFormatLayer;
	delete iGlobalText;
}

void CPaperclipModel::Reset()
{
};
