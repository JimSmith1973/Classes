// ClipboardClass.cpp

#include "ClipboardClass.h"

Clipboard::Clipboard()
{
} // End of function Clipboard::Clipboard
 
Clipboard::~Clipboard()
{
} // End of function Clipboard::~Clipboard

BOOL Clipboard::GetText( LPTSTR lpszText )
{
	BOOL bResult = FALSE;

	// Open clipboard
	if( OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HANDLE hClipboard;

		// Get clipboard data
		hClipboard = GetClipboardData( CF_TEXT );

		// Ensure that clipboard data was got
		if( hClipboard )
		{
			// Successfully got clipboard data
			LPTSTR lpszClipboard;

			// Get clipboard text
			lpszClipboard = static_cast<LPTSTR>( GlobalLock( hClipboard ) );

			// Ensure that clipboard text was got
			if( lpszClipboard )
			{
				// Successfully got clipboard text

				// Update text
				lstrcpy( lpszText, lpszClipboard );

				// Update return value
				bResult = TRUE;

			} // End of successfully got clipboard text

		} // End of successfully got clipboard data

		// Close clipboard
		CloseClipboard();

	} // End of successfully opened clipboard

	return bResult;

} // End of function Clipboard::GetText

DWORD Clipboard::GetTextLength()
{
	DWORD dwResult = FALSE;

	// Open clipboard
	if( OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HANDLE hClipboard;

		// Get clipboard data
		hClipboard = GetClipboardData( CF_TEXT );

		// Ensure that clipboard data was got
		if( hClipboard )
		{
			// Successfully got clipboard data
			LPTSTR lpszText;

			// Get clipboard text
			lpszText = static_cast<LPTSTR>( GlobalLock( hClipboard ) );

			// Ensure that clipboard text was got
			if( lpszText )
			{
				// Successfully got clipboard text

				// Update return value
				dwResult = lstrlen( lpszText );

			} // End of successfully got clipboard text

		} // End of successfully got clipboard data

		// Close clipboard
		CloseClipboard();

	} // End of successfully opened clipboard

	return dwResult;

} // End of function Clipboard::GetTextLength

BOOL Clipboard::SetText( LPCTSTR lpszText )
{
	BOOL bResult = FALSE;

	// Open clipboard
	if( OpenClipboard( NULL ) )
	{
		// Successfully opened clipboard
		HGLOBAL hGlobal;
		DWORD dwBufferLength;

		// Calculate buffer length
		dwBufferLength = ( lstrlen( lpszText ) + sizeof( char ) );

		// Empty clipboard
		EmptyClipboard();

		// Allocate global memory
		hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwBufferLength );

		// Ensure that global memory was allocated
		if( hGlobal )
		{
			// Successfully allocated global memory

			// Copy selected text into global memory
			memcpy( GlobalLock( hGlobal ), lpszText, dwBufferLength );

			// Unlock global memory
			GlobalUnlock( hGlobal );

			// Update clipboard
			if( SetClipboardData( CF_TEXT, hGlobal ) )
			{
				// Successfully updated clipboard

				// Update return value
				bResult = TRUE;

			} // End of successfully updated clipboard

			// Free global memory
			GlobalFree( hGlobal );

		} // End of successfully allocated global memory

		// Close clipboard
		CloseClipboard();

	} // End of successfully opened clipboard

	return bResult;

} // End of function Clipboard::SetText

/*
Clipboard::
{
} // End of function Clipboard::
*/