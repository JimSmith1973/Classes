// HtmlFileClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "FileClass.h"

#define HTML_FILE_CLASS_START_OF_TAG_CHARACTER									'<'
#define HTML_FILE_CLASS_END_OF_TAG_CHARACTER									'>'

#define HTML_FILE_CLASS_PROCESS_TAGS_STATUS_MESSAGE_FORMAT_STRING				"%s (%d tags)"

class HtmlFile : public File
{
public:
	HtmlFile();
	~HtmlFile();

	int ProcessTags( void( *lpTagFunction )( LPCTSTR lpszTag ) );

protected:

}; // End of class HtmlFile
