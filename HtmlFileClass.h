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

#define HTML_FILE_CLASS_ABSOLUTE_URL_IDENTIFIER									"://"

#define HTML_FILE_CLASS_END_OF_TAG_NAME_CHARACTERS								" >"
#define HTML_FILE_CLASS_EDGE_OF_ATTRIBUTE_VALUE_CHARACTERS						"\"'"

#define HTML_FILE_CLASS_ANCHOR_TAG_NAME											"a"
#define HTML_FILE_CLASS_ANCHOR_TAG_ATTRIBUTE									"href"

#define HTML_FILE_CLASS_PROCESS_TAGS_STATUS_MESSAGE_FORMAT_STRING				"%s (%d tags)"

class HtmlFile : public File
{
public:
	HtmlFile();
	~HtmlFile();

	int ProcessTags( LPCTSTR lpszRequiredTagName, LPCTSTR lpszRequiredAttributeName, LPCTSTR lpszParentUrl, void( *lpTagFunction )( LPCTSTR lpszTag, LPCTSTR lpszAttributeValue ) );

protected:

}; // End of class HtmlFile
