// StatusBarWindowClass.cpp

#include "StatusBarWindowClass.h"

StatusBarWindow::StatusBarWindow()
{
} // End of function StatusBarWindow::StatusBarWindow
 
StatusBarWindow::~StatusBarWindow()
{
} // End of function StatusBarWindow::~StatusBarWindow

BOOL StatusBarWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( STATUS_BAR_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function StatusBarWindow::Create

BOOL StatusBarWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function StatusBarWindow::Move

BOOL StatusBarWindow::SetText( LPCTSTR lpszStatusText )
{
	// Set text
	return ::SendMessage( m_hWnd, SB_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszStatusText );

} // End of function StatusBarWindow::SetText

LRESULT StatusBarWindow::Size()
{
	// Size window
	return ::SendMessage( m_hWnd, WM_SIZE, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function StatusBarWindow::Size


/*
StatusBarWindow::
{
} // End of function StatusBarWindow::
*/