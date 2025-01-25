// FileListViewWindowClass.cpp

#include "FileListViewWindowClass.h"

FileListViewWindow::FileListViewWindow()
{
} // End of function FileListViewWindow::FileListViewWindow
 
FileListViewWindow::~FileListViewWindow()
{
} // End of function FileListViewWindow::~FileListViewWindow

BOOL FileListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( ListViewWindow::Create( hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window
		int nWhichColumn;
		LPCTSTR lpszColumnTitles [] = FILE_LIST_VIEW_WINDOW_CLASS_CLASS_COLUMN_TITLES;

		// Add columns to window
		for( nWhichColumn = 0; nWhichColumn < FILE_LIST_VIEW_WINDOW_CLASS_NUMBER_OF_COLUMNS; nWhichColumn ++ )
		{
			// Add column to window
			AddColumn( lpszColumnTitles[ nWhichColumn ] );

		}; // End of loop to add columns to window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function FileListViewWindow::Create

BOOL FileListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) )
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

} // End of function FileListViewWindow::HandleNotifyMessage

BOOL FileListViewWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
{
	BOOL bResult = FALSE;

	// Move window
	if( ListViewWindow::Move( nLeft, nTop, nWidth, nHeight, bRepaint ) )
	{
		// Successfully moved window

		// Update return value
		bResult = TRUE;

	} // End of successfully moved window

	return bResult;

} // End of function FileListViewWindow::Move

/*
FileListViewWindow::
{
} // End of function FileListViewWindow::
*/