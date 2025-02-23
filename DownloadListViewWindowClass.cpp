// DownloadListViewWindowClass.cpp

#include "DownloadListViewWindowClass.h"

DownloadListViewWindow::DownloadListViewWindow()
{
	// Initialise member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function DownloadListViewWindow::DownloadListViewWindow
 
DownloadListViewWindow::~DownloadListViewWindow()
{
	// Clear member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function DownloadListViewWindow::~DownloadListViewWindow

DownloadListViewWindow& DownloadListViewWindow::operator = ( HWND hWnd )
{
	// Update member variables
	m_hWnd = hWnd;

	return *this;

} // End of function DownloadListViewWindow::operator =

BOOL DownloadListViewWindow::operator == ( HWND hWnd )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hWnd == m_hWnd )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function DownloadListViewWindow::operator ==

BOOL DownloadListViewWindow::operator != ( HWND hWnd )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hWnd != m_hWnd )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function DownloadListViewWindow::operator !=

DownloadListViewWindow::operator HWND()
{
	return m_hWnd;

} // End of function DownloadListViewWindow::operator HWND()

BOOL DownloadListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( ListViewWindow::Create( hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window
		int nWhichColumn;
		LPCTSTR lpszColumnTitles [] = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_CLASS_COLUMN_TITLES;

		// Add columns to window
		for( nWhichColumn = 0; nWhichColumn < DOWNLOAD_LIST_VIEW_WINDOW_CLASS_NUMBER_OF_COLUMNS; nWhichColumn ++ )
		{
			// Add column to window
			AddColumn( lpszColumnTitles[ nWhichColumn ] );

		}; // End of loop to add columns to window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function DownloadListViewWindow::Create

/*
DownloadListViewWindow::
{
} // End of function DownloadListViewWindow::
*/