#ifndef __PAPERCLIP_H
#define __PAPERCLIP_H

#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif

// the resource compiler generates the RSG file
// which contains the enums for our resource file
#include <Paperclip.rsg>
// these are the enums shared between both the resource file,
// and the C++ source code, i.e. toolbar & menu command enums
#include "Paperclip.hrh"

#endif