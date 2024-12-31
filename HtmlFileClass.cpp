// HtmlFileClass.cpp

#include "HtmlFileClass.h"

HtmlFile::HtmlFile()
{
} // End of function HtmlFile::HtmlFile
 
HtmlFile::~HtmlFile()
{
} // End of function HtmlFile::~HtmlFile

int HtmlFile::ProcessTags( LPCTSTR lpszRequiredTagName, LPCTSTR lpszRequiredAttributeName, void( *lpTagFunction )( LPCTSTR lpszTag ) )
{
	int nResult = 0;

	LPTSTR lpStartOfTag;
	LPTSTR lpEndOfTag;
	LPTSTR lpEndOfTagName;
	DWORD dwMaximumTagLength = STRING_LENGTH;
	DWORD dwTagLength;

	// Allocate string memory
	LPTSTR lpszTag		= new char[ dwMaximumTagLength + sizeof( char ) ];
	LPTSTR lpszTagName	= new char[ STRING_LENGTH + sizeof( char ) ];

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

				// See if tag has the required name
				if( lstrcmpi( lpszTagName, lpszRequiredTagName ) == 0 )
				{
					// Tag has the required name

					// Process tag
					( *lpTagFunction )( lpszTag );

					// Update return value
					nResult ++;

				} // End of tag has the required name

			} // End of successfully found end of tag name

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
	delete [] lpszTagName;

	return nResult;

} // End of function HtmlFile::ProcessTags

/*
HtmlFile::
{
} // End of function HtmlFile::
*/