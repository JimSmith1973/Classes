// ButtonWindowClass.cpp

#include "ButtonWindowClass.h"

ButtonWindow::ButtonWindow()
{
} // End of function ButtonWindow::ButtonWindow
 
ButtonWindow::~ButtonWindow()
{
} // End of function ButtonWindow::~ButtonWindow

BOOL ButtonWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, int nID, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( BUTTON_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, ( HMENU )( INT_PTR )nID, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function ButtonWindow::Create

BOOL ButtonWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function ButtonWindow::Move

/*
ButtonWindow::
{
} // End of function ButtonWindow::
*/