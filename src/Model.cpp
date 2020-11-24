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
//==============================================================================
{
    CPaperclipModel* self = new( ELeave ) CPaperclipModel();
    CleanupStack::PushL( self );

    self->ConstructL();
    
    CleanupStack::Pop();  // self
    return self;
}

void CPaperclipModel::ConstructL()
//==============================================================================
{
    // create a default usable Normal style (the default layers);
    // this snippet taken from the Psion Word source code
    CParaFormat     paraFormat;
    TParaFormatMask paraFormatMask;
    paraFormat.iHorizontalAlignment = CParaFormat::ELeftAlign;
    paraFormatMask.SetAttrib( EAttAlignment );

    // the paragraph format is kept in the model
    iParaFormatLayer = CParaFormatLayer::NewL(
        &paraFormat, paraFormatMask
    );

    TCharFormat     charFormat;
    TCharFormatMask charFormatMask;
    TInt typefaceAttributes = TTypeface::ESerif;
    charFormat.iFontSpec.iTypeface.SetAttributes( typefaceAttributes );
    charFormat.iFontSpec.iHeight = 200;
    charFormatMask.SetAttrib( EAttFontTypeface );
    charFormatMask.SetAttrib( EAttFontHeight );

    // the character format is kept in the model
    iCharFormatLayer = CCharFormatLayer::NewL(
        charFormat, charFormatMask
    );
    
    iGlobalText = CGlobalText::NewL(
        iParaFormatLayer,
        iCharFormatLayer,
        CEditableText::ESegmentedStorage,
        CEditableText::EDefaultTextGranularity
    );
}

CPaperclipModel::~CPaperclipModel()
//==============================================================================
{
    delete iGlobalText;
    delete iCharFormatLayer;
    delete iParaFormatLayer;
}

void CPaperclipModel::Reset()
{}
