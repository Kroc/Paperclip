#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "HPaperclip.h" 
#include "HApp.h"


class CPaperclipApplication
	: public CEikApplication
{
private:
	//--------------------------------------------------------------------------
	// CApaApplication::
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
};

#endif