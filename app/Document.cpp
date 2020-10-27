#include "Document.h"
#include "AppUI.h"

CPaperclipDocument::CPaperclipDocument(
	CEikApplication& aApp		// EIKON application reference
) : CEikDocument(aApp)
{
}

CPaperclipDocument* CPaperclipDocument::NewL(
	CEikApplication& aApp		// EIKON application reference
){
	CPaperclipDocument* self = new (ELeave) CPaperclipDocument(aApp);
	CleanupStack::PushL( self );
	self->ConstructL();
	self->ResetModelL();
	CleanupStack::Pop(); // self
	return self;
}

void CPaperclipDocument::ConstructL()
{
	// construct the application model (internal state);
	// a pointer to this is passed to the views so that
	// they can access the shared data and methods
	//
	iModel = CPaperclipModel::NewL();
}

CPaperclipDocument::~CPaperclipDocument()
{
	delete iModel;
}

void CPaperclipDocument::ResetModelL()
{
	iModel->Reset();
}

CEikAppUi* CPaperclipDocument::CreateAppUiL()
{
    return new(ELeave) CPaperclipAppUi;
}
