#include <e32std.h>

#include "Application.h"
#include "Document.h"

GLDEF_C TInt E32Dll(TDllReason)
//==============================================================================
{
    return KErrNone;
}

GLREF_C void Panic(TInt aReason)
{
    User::Panic(
        // note that, per the SDK,
        // this string is limited to 16 chars
        _L("Paperclip"), aReason
    );
}

EXPORT_C CApaApplication* NewApplication()
//==============================================================================
{
    return new CPaperclipApplication;
}

TUid CPaperclipApplication::AppDllUid() const
//==============================================================================
{
    // see "application.h" for definition
    return KUidPaperclipApp;
}

CApaDocument* CPaperclipApplication::CreateDocumentL()
//==============================================================================
{
    return CPaperclipDocument::NewL(*this);
}
