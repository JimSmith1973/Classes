// HtmlFileClass.cpp

#include "HtmlFileClass.h"

HtmlFile::HtmlFile()
{
} // End of function HtmlFile::HtmlFile
 
HtmlFile::~HtmlFile()
{
} // End of function HtmlFile::~HtmlFile

int HtmlFile::ProcessTags( LPCTSTR lpszRequiredTagName, LPCTSTR lpszRequiredAttributeName, LPCTSTR lpszParentUrl, void( *lpTagFunction )( LPCTSTR lpszTag, LPCTSTR lpszAttributeValue ) )
{
	int nResult = 0;

	LPTSTR lpStartOfTag;
	LPTSTR lpStartOfAttribute;
	LPTSTR lpStartOfAttributeValue;
	LPTSTR lpEndOfAttributeValue;
	LPTSTR lpEndOfTag;
	LPTSTR lpEndOfTagName;
	DWORD dwMaximumTagLength = STRING_LENGTH;
	DWORD dwTagLength;

	// Allocate string memory
	LPTSTR lpszTag						= new char[ dwMaximumTagLength + sizeof( char ) ];
	LPTSTR lpszTagName					= new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszAbsoluteAttributeValue	= new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszRelativeAttributeValue	= new char[ STRING_LENGTH + sizeof( char ) ];

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

					// Find attribute in tag
					lpStartOfAttribute = strstr( lpszTag, lpszRequiredAttributeName );

					// Ensure that attribute was found in tag
					if( lpStartOfAttribute )
					{
						// Successfully found attribute in tag

						// Find start of atttribute value
						lpStartOfAttributeValue = strpbrk( lpStartOfAttribute, HTML_FILE_CLASS_EDGE_OF_ATTRIBUTE_VALUE_CHARACTERS );

						// Ensure that start of atttribute value was found
						if( lpStartOfAttributeValue )
						{
							// Successfully found start of atttribute value

							// Store relative attribute value
							lstrcpy( lpszRelativeAttributeValue, ( lpStartOfAttributeValue + sizeof( char ) ) );

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
									lstrcpy( lpszAbsoluteAttributeValue, lpszRelativeAttributeValue );

								} // End of attribute value is absolute
								else
								{
									// Attribute value is not absolute

									// Copy parent url into absolute attribute
									lstrcpy( lpszAbsoluteAttributeValue, lpszParentUrl );

									// Ensure that absolute attribute value ends with a forward slash
									if( lpszAbsoluteAttributeValue[ lstrlen( lpszAbsoluteAttributeValue ) - sizeof( char ) ] != ASCII_FORWARD_SLASH_CHARACTER )
									{
										// Absolute attribute value does not end with a forward slash

										// Append a forward slash onto absolute attribute value
										lstrcat( lpszAbsoluteAttributeValue, ASCII_FORWARD_SLASH_STRING );

									} // End of absolute attribute value does not end with a forward slash
									
									// See if relative attribute value begins with a forward slash
									if( lpszRelativeAttributeValue[ 0 ] == ASCII_FORWARD_SLASH_CHARACTER )
									{
										// Relative attribute value begins with a forward slash

										// Append relative attribute (after forward slash) onto absolute attribute value
										lstrcat( lpszAbsoluteAttributeValue, ( lpszRelativeAttributeValue + sizeof( char ) ) );

									} // End of relative attribute value begins with a forward slash
									else
									{
										// Relative attribute value does not begin with a forward slash

										// Append relative attribute onto absolute attribute value
										lstrcat( lpszAbsoluteAttributeValue, lpszRelativeAttributeValue );

									} // End of relative attribute value begins does not begin a forward slash

								} // End of attribute value is not absolute

								// Process tag
								( *lpTagFunction )( lpszTag, lpszAbsoluteAttributeValue );

								// Update return value
								nResult ++;

							} // End of successfully found end of attribute value

						} // End of successfully found start of atttribute value

					} // End of successfully found attribute in tag

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
	delete [] lpszAbsoluteAttributeValue;
	delete [] lpszRelativeAttributeValue;

	return nResult;

} // End of function HtmlFile::ProcessTags

/*
HtmlFile::
{
} // End of function HtmlFile::
*/