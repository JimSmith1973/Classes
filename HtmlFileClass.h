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

#define HTML_FILE_CLASS_IMAGE_TAG_NAME											"img"
#define HTML_FILE_CLASS_IMAGE_TAG_ATTRIBUTE										"src"
#define HTML_FILE_CLASS_IMAGE_TAG_TITLE											"Image"

#define HTML_FILE_CLASS_START_OF_END_TAG_NAME_CHARACTER							'/'

#define HTML_FILE_CLASS_STRING_SURROUND_CHARACTERS								"\"'"

#define HTML_FILE_CLASS_UNKNOWN_TAG_TITLE										"Unknown"

#define HTML_FILE_CLASS_PROCESS_TAGS_STATUS_MESSAGE_FORMAT_STRING				"%s (%d tags)"
#define HTML_FILE_CLASS_PROCESS_STRINGS_STATUS_MESSAGE_FORMAT_STRING			"%s (%d items)"

class HtmlFile : public File
{
public:
	HtmlFile();
	~HtmlFile();

	BOOL GetAbsoluteUrl( LPCTSTR lpszInitialUrl, LPCTSTR lpszParentUrl, LPTSTR lpszAbsoluteUrl );

	BOOL GetAttributeValue( LPCTSTR lpszTag, LPCTSTR lpszParentUrl, LPCTSTR lpszAttributeName, LPTSTR lpszAttributeValue );

	BOOL GetTagName( LPCTSTR lpszTag, LPTSTR lpszTagName );

	int ProcessStrings( LPCTSTR lpszStringMustContain, LPCTSTR lpszExtra, BOOL( *lpStringFunction )( LPCTSTR lpszString, LPCTSTR lpszExtra ) );

	int ProcessTags( LPCTSTR lpszParentUrl, void( *lpTagFunction )( LPCTSTR lpszParentUrl, LPCTSTR lpszTag ) );

protected:

}; // End of class HtmlFile
