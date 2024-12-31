// EditWindowClass.cpp

#include "EditWindowClass.h"

EditWindow::EditWindow()
{
} // End of function EditWindow::EditWindow
 
EditWindow::~EditWindow()
{
} // End of function EditWindow::~EditWindow

BOOL EditWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( EDIT_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function EditWindow::Create

BOOL EditWindow::HandleCommandMessage( WPARAM wParam, LPARAM, void( *lpUpdateFunction )( int nTextLength ) )
{
	BOOL bResult = FALSE;

	// Select command
	switch( HIWORD( wParam ) )
	{
		case EN_UPDATE:
		{
			// An edit window update command
			int nTextLength;

			// Get text length
			nTextLength = ::SendMessage( m_hWnd, WM_GETTEXTLENGTH, ( WPARAM )NULL, ( LPARAM )NULL );

			// Call update function
			( *lpUpdateFunction )( nTextLength );

			// Break out of switch
			break;

		} // End of an update command

	}; // End of selection for command

	return bResult;

} // End of function EditWindow::HandleCommandMessage

BOOL EditWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function EditWindow::Move

void EditWindow::SelectText( int nStart, int nEnd )
{
	// Select text
	::SendMessage( m_hWnd, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function EditWindow::SelectText

/*
EditWindow::
*/