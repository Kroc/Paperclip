// model (internal state) for the application:
//
#include "Model.h"

CPaperclipModel::CPaperclipModel()
{
    __DECLARE_NAME( _S( "CPaperclipModel" ));
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

    // the paragraph format layer is kept in the model
    iParaFormatLayer = CParaFormatLayer::NewL(
        &paraFormat, paraFormatMask
    );

    TCharFormat     charFormat;
    TCharFormatMask charFormatMask;
    charFormat.iFontSpec.iTypeface.SetAttributes( TTypeface::ESerif );
    charFormatMask.SetAttrib( EAttFontTypeface );

    // the character format layer is kept in the model
    iCharFormatLayer = CCharFormatLayer::NewL(
        charFormat, charFormatMask
    );

	// instantiate the text storage object, passing our paragraph
	// and character formats to be used for all text therein
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

TStreamId CPaperclipModel::StoreL(
	CStreamStore& aStore
) const
//==============================================================================
{
	// open the data-stream based on the given data-store:
	// `CreateLC` will open the stream, returning an ID, automatically placing
	// the stream object on the clean-up stack so that any fail further down
	// the line will not leave the stream object orphaned
	//
	RStoreWriteStream stream;
    TStreamId stream_id = stream.CreateLC( aStore );
    
	ExternalizeL( stream );
    
	stream.CommitL();
	CleanupStack::PopAndDestroy();

    return stream_id;
}

// write the data-memebers of the model to the data-store
//
void CPaperclipModel::ExternalizeL(
	RWriteStream& aStream
) const
//==============================================================================
{
}