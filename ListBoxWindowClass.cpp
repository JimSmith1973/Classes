// ListBoxWindowClass.cpp

#include "ListBoxWindowClass.h"

ListBoxWindow::ListBoxWindow()
{
} // End of function ListBoxWindow::ListBoxWindow
 
ListBoxWindow::~ListBoxWindow()
{
} // End of function ListBoxWindow::~ListBoxWindow

int ListBoxWindow::AddString( LPCTSTR lpszString )
{
	// Add string
	return ::SendMessage( m_hWnd, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszString );

} // End of function ListBoxWindow::AddString

int ListBoxWindow::AddText( LPCTSTR lpszText )
{
	// Add text
	return ::SendMessage( m_hWnd, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszText );

} // End of function ListBoxWindow::AddText

int ListBoxWindow::AddTextEx( LPCTSTR lpszText )
{
	int nResult;

	// Add text
	nResult = ::SendMessage( m_hWnd, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszText );

	// Ensure that text was added
	if( nResult >= 0 )
	{
		// Successfully added text

		// Ensure that text is visible
		::SendMessage( m_hWnd, LB_SETTOPINDEX, ( WPARAM )nResult, ( LPARAM )NULL );

		// Update window
		::UpdateWindow( m_hWnd );

	} // End of successfully added text

	return nResult;

} // End of function ListBoxWindow::AddTextEx

BOOL ListBoxWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( LIST_BOX_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created windowW

	return bResult;

} // End of function ListBoxWindow::Create

int ListBoxWindow::GetCurrentSelection()
{
	// Get current selection
	return ::SendMessage( m_hWnd, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function ListBoxWindow::GetCurrentSelection

int ListBoxWindow::GetText( int nWhichItem, LPTSTR lpszText )
{
	// Get text
	return ::SendMessage( m_hWnd, LB_GETTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszText );

} // End of function ListBoxWindow::GetText


BOOL ListBoxWindow::HandleCommandMessage( WPARAM wParam, LPARAM, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select list box window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_SELCHANGE:
		{
			// A list box window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = ::SendMessage( m_hWnd, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( ::SendMessage( m_hWnd, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
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
		case LBN_DBLCLK:
		{
			// A list box window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelected = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = ::SendMessage( m_hWnd, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get selected item text
			if( ::SendMessage( m_hWnd, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
			{
				// Successfully got selected item text

				// Call double click function
				( *lpDoubleClickFunction )( lpszSelected );

				// Update return value
				bResult = TRUE;

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelected;

			// Break out of switch
			break;

		} // End of a list box window double click notification code
		default:
		{
			// Default list box window notification code

			// Don't need to do anything here, just return with default result

			// Break out of switch
			break;

		} // End of default list box window notification code

	}; // End of selection for list box window notification code

	return bResult;

} // End of function ListBoxWindow::HandleCommandMessage

BOOL ListBoxWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function ListBoxWindow::Move

/*
ListBoxWindow::
{
} // End of function ListBoxWindow::
*/