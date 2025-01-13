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