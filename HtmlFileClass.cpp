// HtmlFileClass.cpp

#include "HtmlFileClass.h"

HtmlFile::HtmlFile()
{
} // End of function HtmlFile::HtmlFile
 
HtmlFile::~HtmlFile()
{
} // End of function HtmlFile::~HtmlFile

int HtmlFile::ProcessTags( void( *lpTagFunction )( LPCTSTR lpszTag ) )
{
	int nResult = 0;

	LPTSTR lpszStartOfTag;
	LPTSTR lpszEndOfTag;
	DWORD dwMaximumTagLength = STRING_LENGTH;
	DWORD dwTagLength;

	// Allocate string memory
	LPTSTR lpszTag = new char[ dwMaximumTagLength + sizeof( char ) ];

	// Find start of first tag
	lpszStartOfTag = strchr( m_lpszFileText, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

	// Loop through all tags
	while( lpszStartOfTag )
	{
		// Find end of tag
		lpszEndOfTag = strchr( lpszStartOfTag, HTML_FILE_CLASS_END_OF_TAG_CHARACTER );

		// Ensure that end of tag was found
		if( lpszEndOfTag )
		{
			// Successfully found end of tag

			// Calculate tag length
			dwTagLength = ( ( lpszEndOfTag - lpszStartOfTag ) + sizeof( char ) );

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
			lstrcpyn( lpszTag, lpszStartOfTag, ( dwTagLength + sizeof( char ) ) );

			// Process tag
			( *lpTagFunction )( lpszTag );

			// Update return value
			nResult ++;

			// Find start of next tag
			lpszStartOfTag = strchr( lpszEndOfTag, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

		} // End of successfully found end of tag
		else
		{
			// Unable to find end of tag

			// Force exit from loop
			lpszStartOfTag = NULL;

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