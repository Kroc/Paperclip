#ifndef __MODEL_H
#define __MODEL_H

#include "HEikon.h"

#include <txtglobl.h>			// CGlobalText
#include <txtfmlyr.h>			// CParaFormatLayer, CCharFormatLayer

class CPaperclipModel : CBase
{
public:
	//--------------------------------------------------------------------------
	CPaperclipModel();			// constructor
	~CPaperclipModel();			// destructor

	static CPaperclipModel* NewL();
	void ConstructL();

	TStreamId StoreL(CStreamStore& aStore) const;
	void ExternalizeL(RWriteStream& aStream) const;

public:
	//--------------------------------------------------------------------------
	// return the handle to the text-storage object
	CGlobalText* GlobalText(){ return iGlobalText; };

private:
	//--------------------------------------------------------------------------
	// this is the actual text storage in RAM
	CGlobalText* iGlobalText;

	// this is the font/paragraph style used for the text-editor;
	// since it's not a rich-text editor, the same style is used
	// for all text in the editor
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
};

#endif