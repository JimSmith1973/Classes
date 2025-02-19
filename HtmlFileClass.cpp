// HtmlFileClass.cpp

#include "HtmlFileClass.h"

HtmlFile::HtmlFile()
{
} // End of function HtmlFile::HtmlFile
 
HtmlFile::~HtmlFile()
{
} // End of function HtmlFile::~HtmlFile

BOOL HtmlFile::GetAbsoluteUrl( LPCTSTR lpszInitialUrl, LPCTSTR lpszParentUrl, LPTSTR lpszAbsoluteUrl )
{
	BOOL bResult = FALSE;

	// See if initial url is absolute
	if( strstr( lpszInitialUrl, HTML_FILE_CLASS_ABSOLUTE_URL_IDENTIFIER ) )
	{
		// Initial url is absolute

		// Copy initial url into absolute url
		lstrcpy( lpszAbsoluteUrl, lpszInitialUrl );

	} // End of initial url is absolute
	else
	{
		// Initial url is not absolute

		// Copy parent url into absolute url
		lstrcpy( lpszAbsoluteUrl, lpszParentUrl );

		// Ensure that absolute url ends with a forward slash
		if( lpszAbsoluteUrl[ lstrlen( lpszAbsoluteUrl ) - sizeof( char ) ] != ASCII_FORWARD_SLASH_CHARACTER )
		{
			// Absolute url does not end with a forward slash

			// Append a forward slash onto absolute url
			lstrcat( lpszAbsoluteUrl, ASCII_FORWARD_SLASH_STRING );

		} // End of absolute url does not end with a forward slash

		// See if initial url begins with a forward slash
		if( lpszInitialUrl[ 0 ] == ASCII_FORWARD_SLASH_CHARACTER )
		{
			// Initial url begins with a forward slash

			// Append initial url (after forward slash) onto absolute url
			lstrcat( lpszAbsoluteUrl, ( lpszInitialUrl + sizeof( char ) ) );

		} // End of initial url begins with a forward slash
		else
		{
			// Initial url does not begin with a forward slash

			// Append initial url onto absolute url
			lstrcat( lpszAbsoluteUrl, lpszInitialUrl );

		} // End of initial url begins does not begin a forward slash

	} // End of initial url is not absolute

	return bResult;

} // End of function HtmlFile::GetAbsoluteUrl

BOOL HtmlFile::GetAttributeValue( LPCTSTR lpszTag, LPCTSTR lpszParentUrl, LPCTSTR lpszAttributeName, LPTSTR lpszAttributeValue )
{
	BOOL bResult = FALSE;

	LPTSTR lpStartOfAttribute;

	// Find attribute in tag
	lpStartOfAttribute = strstr( lpszTag, lpszAttributeName );

	// Ensure that attribute was found in tag
	if( lpStartOfAttribute )
	{
		// Successfully found attribute in tag
		LPTSTR lpStartOfAttributeValue;

		// Find start of atttribute value
		lpStartOfAttributeValue = strpbrk( lpStartOfAttribute, HTML_FILE_CLASS_EDGE_OF_ATTRIBUTE_VALUE_CHARACTERS );

		// Ensure that start of atttribute value was found
		if( lpStartOfAttributeValue )
		{
			// Successfully found start of atttribute value
			LPTSTR lpEndOfAttributeValue;

			// Allocate string memory
			LPTSTR lpszRelativeAttributeValue = new char[ STRING_LENGTH + sizeof( char ) ];

			// Store relative attribute value
			lstrcpyn( lpszRelativeAttributeValue, ( lpStartOfAttributeValue + sizeof( char ) ), STRING_LENGTH );

			// Find end of relative attribute value
			lpEndOfAttributeValue = strpbrk( lpszRelativeAttributeValue, HTML_FILE_CLASS_EDGE_OF_ATTRIBUTE_VALUE_CHARACTERS );

			// See if end of attribute value was found
			if( lpEndOfAttributeValue )
			{
				// Successfully found end of attribute value

				// Terminate attribute value
				lpEndOfAttributeValue[ 0 ] = ( char )NULL;

				// See if attribute value is absolute
				if( strstr( lpszRelativeAttributeValue, HTML_FILE_CLASS_ABSOLUTE_URL_IDENTIFIER ) )
				{
					// Attribute value is absolute

					// Copy attribute into absolute attribute
					lstrcpy( lpszAttributeValue, lpszRelativeAttributeValue );

				} // End of attribute value is absolute
				else
				{
					// Attribute value is not absolute

					// Copy parent url into absolute attribute
					lstrcpy( lpszAttributeValue, lpszParentUrl );

					// Ensure that absolute attribute value ends with a forward slash
					if( lpszAttributeValue[ lstrlen( lpszAttributeValue ) - sizeof( char ) ] != ASCII_FORWARD_SLASH_CHARACTER )
					{
						// Absolute attribute value does not end with a forward slash

						// Append a forward slash onto absolute attribute value
						lstrcat( lpszAttributeValue, ASCII_FORWARD_SLASH_STRING );

					} // End of absolute attribute value does not end with a forward slash

					// See if relative attribute value begins with a forward slash
					if( lpszRelativeAttributeValue[ 0 ] == ASCII_FORWARD_SLASH_CHARACTER )
					{
						// Relative attribute value begins with a forward slash

						// Append relative attribute (after forward slash) onto absolute attribute value
						lstrcat( lpszAttributeValue, ( lpszRelativeAttributeValue + sizeof( char ) ) );

					} // End of relative attribute value begins with a forward slash
					else
					{
						// Relative attribute value does not begin with a forward slash

						// Append relative attribute onto absolute attribute value
						lstrcat( lpszAttributeValue, lpszRelativeAttributeValue );

					} // End of relative attribute value begins does not begin a forward slash

				} // End of attribute value is not absolute

				// Update return value
				bResult = TRUE;

			} // End of successfully found end of attribute value

			// Free string memory
			delete [] lpszRelativeAttributeValue;

		} // End of successfully found start of atttribute value

	} // End of successfully found attribute in tag

	return bResult;

} // End of function HtmlFile::GetAttributeValue

BOOL HtmlFile::GetTagName( LPCTSTR lpszTag, LPTSTR lpszTagName )
{
	BOOL bResult = FALSE;

	LPTSTR lpEndOfTagName;

	// Set start of tag name
	lstrcpyn( lpszTagName, ( lpszTag + sizeof( char ) ), STRING_LENGTH );

	// Find end of tag name
	lpEndOfTagName = strpbrk( lpszTagName, HTML_FILE_CLASS_END_OF_TAG_NAME_CHARACTERS );

	// Ensure that end of tag name was found
	if( lpEndOfTagName )
	{
		// Successfully found end of tag name

		// Terminate tag name
		lpEndOfTagName[ 0 ] = ( char )NULL;

		// Update return value
		bResult = TRUE;

	} // End of successfully found end of tag name

	return bResult;

} // End of function HtmlFile::GetTagName

int HtmlFile::ProcessStrings( LPCTSTR lpszStringMustContain, LPCTSTR lpszExtra, BOOL( *lpStringFunction )( LPCTSTR lpszString, LPCTSTR lpszExtra ) )
{
	int nResult = 0;

	LPTSTR lpszStartOfString;
	LPTSTR lpszEndOfString;
	DWORD dwStringLength;

	// Allocate string memory
	LPTSTR lpszString = new char[ STRING_LENGTH + sizeof( char ) ];

	// Find start of first string
	lpszStartOfString = strpbrk( m_lpszFileText, HTML_FILE_CLASS_STRING_SURROUND_CHARACTERS );

	// Loop through all strings
	while( lpszStartOfString )
	{
		// Find end of string
		lpszEndOfString = strchr( ( lpszStartOfString + sizeof( char ) ), lpszStartOfString[ 0 ] );

		// Ensure that end of string was found
		if( lpszEndOfString )
		{
			// Successfully found end of string

			// Calculate string length
			dwStringLength = ( ( lpszEndOfString - lpszStartOfString ) - sizeof( char ) );

			// Ensure that string is not too long
			if( dwStringLength > STRING_LENGTH )
			{
				// String is too long

				// Limit string length
				dwStringLength = STRING_LENGTH;

			} // End of string is too long

			// Store string
			lstrcpyn( lpszString, ( lpszStartOfString + sizeof( char ) ), ( dwStringLength + sizeof( char ) ) );

			// See if string contains required text
			if( strstr( lpszString, lpszStringMustContain ) )
			{
				// String contains required text

				// Process string
				if( ( *lpStringFunction )( lpszString, lpszExtra ) )
				{
					// Successfully processed string

					// Update return value
					nResult ++;

				} // End of successfully processed string

			} // End of string contains required text

			// Find start of next string
			lpszStartOfString = strpbrk( ( lpszEndOfString + sizeof( char ) ), HTML_FILE_CLASS_STRING_SURROUND_CHARACTERS );

		} // End of successfully found end of string
		else
		{
			// Unable to find end of string

			// Force exit from loop
			lpszStartOfString = NULL;

		} // End of unable to find end of string

	}; // End of loop through all strings

	// Free string memory
	delete [] lpszString;

	return nResult;

} // End of function HtmlFile::ProcessStrings

int HtmlFile::ProcessTags( LPCTSTR lpszParentUrl, void( *lpTagFunction )( LPCTSTR lpszParentUrl, LPCTSTR lpszTag ) )
{
	int nResult = 0;

	LPTSTR lpStartOfTag;
	LPTSTR lpEndOfTag;
	DWORD dwMaximumTagLength = STRING_LENGTH;
	DWORD dwTagLength;

	// Allocate string memory
	LPTSTR lpszTag = new char[ dwMaximumTagLength + sizeof( char ) ];

	// Find start of first tag
	lpStartOfTag = strchr( m_lpszFileText, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

	// Loop through all tags
	while( lpStartOfTag )
	{
		// Find end of tag
		lpEndOfTag = strchr( lpStartOfTag, HTML_FILE_CLASS_END_OF_TAG_CHARACTER );

		// Ensure that end of tag was found
		if( lpEndOfTag )
		{
			// Successfully found end of tag

			// Calculate tag length
			dwTagLength = ( ( lpEndOfTag - lpStartOfTag ) + sizeof( char ) );

			// Ensure that tag length is ok
			if( dwTagLength > dwMaximumTagLength )
			{
				// Tag length is not ok

				// Free string memory
				delete [] lpszTag;

				// Update maximum tag length
				dwMaximumTagLength = dwTagLength;

				// Re-allocate string memory
				lpszTag = new char[ dwMaximumTagLength + sizeof( char ) ];

			} // End of tag length is not ok

			// Store tag
			lstrcpyn( lpszTag, lpStartOfTag, ( dwTagLength + sizeof( char ) ) );

			// Process tag
			( *lpTagFunction )( lpszParentUrl, lpszTag );

			// Update return value
			nResult ++;

			// Find start of next tag
			lpStartOfTag = strchr( lpEndOfTag, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

		} // End of successfully found end of tag
		else
		{
			// Unable to find end of tag

			// Force exit from loop
			lpStartOfTag = NULL;

		} // End of unable to find end of tag

	}; // End of loop through all tags

	// Free string memory
	delete [] lpszTag;

	return nResult;

} // End of function HtmlFile::ProcessTags

/*
HtmlFile::
{
} // End of function HtmlFile::
*/