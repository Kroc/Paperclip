// header file for Paperclip's own definitions
//
#ifndef __H_PAPERCLIP
#define __H_PAPERCLIP

// UID of app
//
#if defined( _UNICODE )
const TUid KUidPaperclipApp={ 0x1dcda100 };
#else
const TUid KUidPaperclipApp={ 0x1bcda100 };
#endif

// the resource compiler generates the RSG file
// which contains the enums for our resource file
#include <Paperclip.rsg>
// these are the enums shared between both the resource file,
// and the C++ source code, i.e. toolbar & menu command enums
#include "Paperclip.hrh"

#endif