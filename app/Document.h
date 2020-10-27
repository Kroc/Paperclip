#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include "HApp.h"
#include "Model.h"

class CPaperclipDocument
	: public CEikDocument
{
public:
	// construct/destruct
	CPaperclipDocument(CEikApplication& aApp);
	~CPaperclipDocument();

	static CPaperclipDocument* NewL(CEikApplication& aApp);
	
	void ConstructL();
	void ResetModelL();

	// method that returns the current model
	CPaperclipModel* Model(){ return iModel; };

private:
	// EIKON: create application UI
	CEikAppUi* CreateAppUiL();

private:
	// the application's model (internal state)
	CPaperclipModel* iModel;
};

#endif