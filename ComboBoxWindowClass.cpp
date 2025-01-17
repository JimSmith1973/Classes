// ComboBoxWindowClass.cpp

#include "ComboBoxWindowClass.h"

ComboBoxWindow::ComboBoxWindow()
{
} // End of function ComboBoxWindow::ComboBoxWindow
 
ComboBoxWindow::~ComboBoxWindow()
{
} // End of function ComboBoxWindow::~ComboBoxWindow

int ComboBoxWindow::AddString( LPCTSTR lpszString )
{
	// Add string
	return ::SendMessage( m_hWnd, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszString );

} // End of function ComboBoxWindow::AddString

int ComboBoxWindow::AddText( LPCTSTR lpszText )
{
	// Add text
	return ::SendMessage( m_hWnd, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszText );

} // End of function ComboBoxWindow::AddText

BOOL ComboBoxWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, int nID, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( COMBO_BOX_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, ( HMENU )( INT_PTR )nID, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function ComboBoxWindow::Create

BOOL ComboBoxWindow::HandleCommandMessage( WPARAM wParam, LPARAM, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select list box window notification code
	switch( HIWORD( wParam ) )
	{
		case CBN_SELCHANGE:
		{
			// A list box window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = ::SendMessage( m_hWnd, CB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( ::SendMessage( m_hWnd, CB_GETLBTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Call selection changed function
				( *lpSelectionChangedFunction )( lpszSelected );

				// Update return value
				bResult = TRUE;

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a list box window selection change notification code

	}; // End of selection for list box window notification code

	return bResult;

} // End of function ComboBoxWindow::HandleCommandMessage

BOOL ComboBoxWindow::Load( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size

			// Allocate string memory
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Delete all items from combo box window
			::SendMessage( m_hWnd, CB_RESETCONTENT, ( WPARAM )NULL, ( LPARAM )NULL );

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text
				LPTSTR lpszItem;

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Get first item from file text
				lpszItem = strtok( lpszFileText, NEW_LINE_TEXT );

				// Loop through all items
				while( lpszItem )
				{
					// Add item to combo box window
					::SendMessage( m_hWnd, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszItem );

					// Get next item from file text
					lpszItem = strtok( NULL, NEW_LINE_TEXT );

				}; // End of loop through all items

				// Update trturn value
				bResult = TRUE;

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function ComboBoxWindow::Load

BOOL ComboBoxWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
{
	BOOL bResult = FALSE;

	// Move window
	if( Window::Move( nLeft, nTop, nWidth, nHeight, bRepaint ) )
	{
		// Successfully moved window

		// Update return value
		bResult = TRUE;

	} // End of successfully moved window

	return bResult;

} // End of function ComboBoxWindow::Move

BOOL ComboBoxWindow::Save( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		int nItemCount;
		int nWhichItem;

		// Allocate string memory
		LPTSTR lpszItemText = new char[ STRING_LENGTH ];

		// Count items on combo box window
		nItemCount = ::SendMessage( m_hWnd, CB_GETCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Update return value (assume success)
		bResult = TRUE;

		// Loop through items on combo box window
		for( nWhichItem = 0; nWhichItem < nItemCount; nWhichItem ++ )
		{
			// Get item text
			if( ::SendMessage( m_hWnd, CB_GETLBTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszItemText ) )
			{
				// Successfully got item text

				// Write item text to file
				if( WriteFile( hFile, lpszItemText, lstrlen( lpszItemText ), NULL, NULL ) )
				{
					// Successfully wrote item text to file

					// Write new line to file
					WriteFile( hFile, NEW_LINE_TEXT, lstrlen( NEW_LINE_TEXT ), NULL, NULL );

				} // End of successfully wrote item text to file
				else
				{
					// Unable to write item text to file

					// Update return value
					bResult = FALSE;

					// Force exit from loop
					nWhichItem = nItemCount;

				} // End of unable to write item text to file

			} // End of successfully got item text
			else
			{
				// Unable to get item text

				// Update return value
				bResult = FALSE;

				// Force exit from loop
				nWhichItem = nItemCount;

			} // End of unable to get item text

		}; // End of loop through items on combo box window

		// Free string memory
		delete [] lpszItemText;

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return bResult;

} // End of function ComboBoxWindow::Save

int ComboBoxWindow::SelectItem( int nWhichItem )
{
	// Select item
	return ::SendMessage( m_hWnd, CB_SETCURSEL, ( WPARAM )nWhichItem, ( LPARAM )NULL );

} // End of function ComboBoxWindow::SelectItem

/*
ComboBoxWindow::
{
} // End of function ComboBoxWindow::
*/