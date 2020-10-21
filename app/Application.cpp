#include "Application.h"
#include "Document.h"

EXPORT_C CApaApplication* NewApplication()
{
	return new CPaperclipApplication;
}

TUid CPaperclipApplication::AppDllUid() const
{
	// see "application.h" for definition
	return KUidPaperclipApp;
}

CApaDocument* CPaperclipApplication::CreateDocumentL()
{
	return CPaperclipDocument::NewL(*this);
}