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
#define HTML_FILE_CLASS_ANCHOR_TAG_TITLE										"Anchor"

#define HTML_FILE_CLASS_UNKNOWN_TAG_TITLE										"Unknown"

#define HTML_FILE_CLASS_PROCESS_TAGS_STATUS_MESSAGE_FORMAT_STRING				"%s (%d tags)"

class HtmlFile : public File
{
public:
	HtmlFile();
	~HtmlFile();

	BOOL GetAttributeValue( LPCTSTR lpszTag, LPCTSTR lpszParentUrl, LPCTSTR lpszAttributeName, LPTSTR lpszAttributeValue );

	BOOL GetTagName( LPCTSTR lpszTag, LPTSTR lpszTagName );

	int ProcessTags( LPCTSTR lpszParentUrl, void( *lpTagFunction )( LPCTSTR lpszParentUrl, LPCTSTR lpszTag ) );

protected:

}; // End of class HtmlFile
