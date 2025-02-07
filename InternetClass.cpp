// InternetClass.cpp

#include "InternetClass.h"

Internet::Internet()
{
	// Initialise member variables
	::ZeroMemory( &m_hInternet, sizeof( m_hInternet ) );

} // End of function Internet::Internet
 
Internet::~Internet()
{
	// Clear member variables
	::ZeroMemory( &m_hInternet, sizeof( m_hInternet ) );

} // End of function Internet::~Internet

Internet& Internet::operator = ( HINTERNET hInternet )
{
	// Update member variables
	m_hInternet = hInternet;

	return *this;

} // End of function Internet::operator =

BOOL Internet::operator == ( HINTERNET hInternet )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hInternet == m_hInternet )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Internet::operator ==

BOOL Internet::operator != ( HINTERNET hInternet )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hInternet != m_hInternet )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Internet::operator !=

Internet::operator HINTERNET()
{
	return m_hInternet;

} // End of function Internet::operator HINTERNET()

BOOL Internet::Close()
{
	// Close connection to internet
	return ::InternetCloseHandle( m_hInternet );

} // End of function Internet::Close

BOOL Internet::Connect( LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags )
{
	BOOL bResult = FALSE;

	// Connect to internet
	m_hInternet = ::InternetOpen( lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags );

	// Ensure that internet was connected to
	if( m_hInternet )
	{
		// Successfully connected ot internet

		// Update return value
		bResult = TRUE;

	} // End of successfully connected ot internet

	return bResult;

} // End of function Internet::Connect

BOOL Internet::DownloadFile( LPCTSTR lpszUrl, LPTSTR lpszLocalFilePath )
{
	BOOL bResult = FALSE;

	// Get current folder into local file path
	if( GetCurrentDirectory( STRING_LENGTH, lpszLocalFilePath ) )
	{
		// Successfully got current folder into local file path
		HINTERNET hInternetFile;
		LPTSTR lpszLastForwardSlash;
		LPTSTR lpszFirstIllegalCharacter;

		// Allocate string memory
		LPTSTR lpszShortUrl = new char[ STRING_LENGTH ];

		// Ensure that local file path ends with a back slash
		if( lpszLocalFilePath[ lstrlen( lpszLocalFilePath ) - sizeof( ASCII_BACK_SLASH_CHARACTER ) ] != ASCII_BACK_SLASH_CHARACTER )
		{
			// Local file path does not end with a back slash

			// Append a back slash onto local file path
			lstrcat( lpszLocalFilePath, ASCII_BACK_SLASH_STRING );

		} // End of local file path does not end with a back slash

		// Copy url
		lstrcpy( lpszShortUrl, lpszUrl );

		// Remove forward slash characters from end of short url
		while( lpszShortUrl[ lstrlen( lpszShortUrl ) - sizeof( char ) ] == ASCII_FORWARD_SLASH_CHARACTER )
		{
			// Remove forward slash character from end of short url
			lpszShortUrl[ lstrlen( lpszShortUrl ) - sizeof( char ) ] = ( char )NULL;

		}; // End of loop to remove forward slash characters from end of short url

		// Find last forward slash in url
		lpszLastForwardSlash = strrchr( lpszShortUrl, ASCII_FORWARD_SLASH_CHARACTER );

		// Ensure that last forward was found slash in url
		if( lpszLastForwardSlash )
		{
			// Successfully found last forward slash in url

			// Append file name onto local file path
			lstrcat( lpszLocalFilePath, ( lpszLastForwardSlash + sizeof( ASCII_FORWARD_SLASH_CHARACTER ) ) );

		} // End of successfully found last forward slash in url
		else
		{
			// Unable to find last forward slash in url

			// Append entire url onto local file path
			lstrcat( lpszLocalFilePath, lpszShortUrl );

		} // End of unable to find last forward slash in url

		// Find any illegal characters in local file path
		lpszFirstIllegalCharacter = strpbrk( lpszLocalFilePath, INTERNET_CLASS_ILLEGAL_FILE_NAME_CHARACTERS );

		// See if any illegal characters were found in local file path
		if( lpszFirstIllegalCharacter )
		{
			// Illegal characters were found in local file path

			// Terminate local file path at first illegal character
			lpszFirstIllegalCharacter[ 0 ] = ( char )NULL;

		} // End of illegal characters were found in local file path

		// Open internet file
		hInternetFile = InternetOpenUrl( m_hInternet, lpszShortUrl, NULL, 0, 0, 0 );

		// Ensure that internet file was opened
		if( hInternetFile )
		{
			// Successfully opened internet file
			HANDLE hLocalFile;

			// Open local file
			hLocalFile = CreateFile( lpszLocalFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

			// Ensure that local file was opened
			if( hLocalFile != INVALID_HANDLE_VALUE )
			{
				// Successfully opened local file
				DWORD dwRead;
				DWORD dwWritten;
				CHAR cBuffer[ INTERNET_CLASS_DOWNLOAD_BUFFER_LENGTH ];

				// Read internet file
				while( InternetReadFile( hInternetFile, cBuffer, INTERNET_CLASS_DOWNLOAD_BUFFER_LENGTH, &dwRead ) )
				{
					// Ensure that data was read into buffer
					if( dwRead == 0 )
					{
						// No data was read into buffer

						// Break out of loop
						break;

					} // End of no data was read into buffer

					// Terminate buffer
					cBuffer[ dwRead ] = ( char )NULL;

					// Write buffer into local file
					WriteFile( hLocalFile, cBuffer, dwRead, &dwWritten, NULL );

				} // End of loop to read internet file

				// Update return value
				bResult = TRUE;

				// Close file
				CloseHandle( hLocalFile );

			} // End of successfully opened local file

			// Close internet file
			InternetCloseHandle( hInternetFile );

		} // End of successfully opened internet file

		// Free string memory
		delete [] lpszShortUrl;

	} // End of successfully got current folder into local file path

	return bResult;

} // End of function Internet::DownloadFile

/*
Internet::
{
} // End of function Internet::
*/