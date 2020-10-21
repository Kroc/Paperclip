#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <eikapp.h>				// for CEikApplication
#include "Paperclip.h"

// UID of app
//
#if defined(_UNICODE)
const TUid KUidPaperclipApp={ 0x1dcda100 };
#else
const TUid KUidPaperclipApp={ 0x1bcda100 };
#endif


class CPaperclipApplication : public CEikApplication
{
private:
	// from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
};

#endif