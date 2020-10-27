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
	CPaperclipModel* self = new(ELeave) CPaperclipModel();
	CleanupStack::PushL( self );

	self->ConstructL();
	
	CleanupStack::Pop();  // self
	return self;
}

void CPaperclipModel::ConstructL()
{
	// Create a default usable Normal style (the default layers);
	// this snippet taken from the Psion Word source code
	// TODO: example the plain-text mode of Word for what formats it uses
	CParaFormat		paraFormat;
	TParaFormatMask paraFormatMask;
	paraFormat.iSpaceAfterInTwips = 100;
	paraFormatMask.SetAttrib( EAttSpaceAfter );
	paraFormat.iHorizontalAlignment = CParaFormat::ELeftAlign;
	paraFormatMask.SetAttrib( EAttAlignment );
	// the paragraph format is kept in the model
	this->iParaFormatLayer=CParaFormatLayer::NewL( &paraFormat,paraFormatMask );
	//
	TCharFormat		charFormat;
	TCharFormatMask charFormatMask;
	TInt typefaceAttributes = TTypeface::EProportional | TTypeface::ESerif;
	charFormat.iFontSpec.iTypeface.SetAttributes( typefaceAttributes );
	charFormat.iFontSpec.iHeight = 200;
	charFormatMask.SetAttrib( EAttFontTypeface );
	charFormatMask.SetAttrib( EAttFontHeight );
	// the character format is kept in the model
	this->iCharFormatLayer=CCharFormatLayer::NewL( charFormat,charFormatMask );

	this->iGlobalText = CGlobalText::NewL(
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
}
