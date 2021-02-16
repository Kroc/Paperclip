#include "Document.h"
#include "AppUI.h"


CPaperclipDocument::CPaperclipDocument(
    CEikApplication& aApp		// EIKON application reference
) : CEikDocument(aApp)
{}

CPaperclipDocument* CPaperclipDocument::NewL(
    CEikApplication& aApp		// EIKON application reference
)
//==============================================================================
{
    CPaperclipDocument* self = new( ELeave ) CPaperclipDocument( aApp );
    CleanupStack::PushL( self );
    
    self->ConstructL();
    
    CleanupStack::Pop(); // self
    return self;
}

void CPaperclipDocument::ConstructL()
//==============================================================================
{
    // construct the application model (internal state);
    // a pointer to this is passed to the views so that
    // they can access the shared data and methods
    //
    iModel = CPaperclipModel::NewL();
	
	// mark the document as dirty (i.e. must be saved)
	SetChanged( ETrue );
}

CEikAppUi* CPaperclipDocument::CreateAppUiL()
//==============================================================================
{
    return new( ELeave ) CPaperclipAppUi;
}

CPaperclipDocument::~CPaperclipDocument()
//==============================================================================
{
    delete iModel;
}

// request to store the document to disk:
//
void CPaperclipDocument::StoreL(
	CStreamStore& aStore,
	CStreamDictionary& aStreamDic
) const
//==============================================================================
{
	// defer to the model to actually write the data...
	TStreamId stream_id = iModel->StoreL( aStore );
	// write the stream ID, together with a UID, to the stream dictionary
    aStreamDic.AssignL( KUidPaperclipApp, stream_id );
}

TBool CPaperclipDocument::IsEmpty() const
//==============================================================================
{
	// the model contains the actual text content
	// for us to check if the editor is empty...

	// if the model has not been created yet
	// the document is, naturally, empty
	if (!iModel) return ETrue;

	return (iModel->GlobalText()->LdDocumentLength() == 0);
}