// TemplateWindowClass.cpp

#include "TemplateWindowClass.h"

TemplateWindow::TemplateWindow()
{
} // End of function TemplateWindow::TemplateWindow
 
TemplateWindow::~TemplateWindow()
{
} // End of function TemplateWindow::~TemplateWindow

BOOL TemplateWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, HMENU hMenu, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( TEMPLATE_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, hMenu, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function TemplateWindow::Create

BOOL TemplateWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) )
{
	BOOL bResult = FALSE;

	LPNMHDR lpNmHdr;

	// Store notify message handler
	lpNmHdr = ( LPNMHDR )lParam;

	// Select notify message
	switch( lpNmHdr->code )
	{
		case TVN_ITEMEXPANDING:
		{
			// An item expanding notify message

			// Break out of switch
			break;

		} // End of an item expanding notify message

	}; // End of selection for notify message

	return bResult;

} // End of function TemplateWindow::HandleNotifyMessage

BOOL TemplateWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function TemplateWindow::Move

/*
TemplateWindow::
{
} // End of function TemplateWindow::
*/