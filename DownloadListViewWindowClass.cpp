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

BOOL DownloadListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), PFNLVCOMPARE lpCompareFunction )
{
	BOOL bResult = FALSE;

	LPNMLISTVIEW lpNmListView;

	// Get list view notify message information
	lpNmListView = ( LPNMLISTVIEW )lParam;

	// Select list view window notification code
	switch( lpNmListView->hdr.code )
	{
		case LVN_COLUMNCLICK:
		{
			// A column click notify message

			// Sort list view window
			::SendMessage( m_hWnd, LVM_SORTITEMSEX, ( WPARAM )( LPARAM )( lpNmListView->iSubItem ), ( LPARAM )lpCompareFunction );

			// Break out of switch
			break;

		} // End of a column click notify message
		case LVN_ITEMCHANGED:
		{
			// A list view window item changed notification code

			// See if selection has changed
			if( ( lpNmListView->uNewState ^ lpNmListView->uOldState ) & LVIS_SELECTED )
			{
				// Selection has changed

				// Allocate string memory
				LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item text
				if( GetItemText( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemText ) )
				{
					// Successfully got item text

					// Call selection changed function
					( *lpSelectionChangedFunction )( lpszItemText );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item text

				// Free string memory
				delete [] lpszItemText;

			} // End of selection has changed

			// Break out of switch
			break;

		} // End of a list view window item changed notification code
		case NM_DBLCLK:
		{
			// A double click notification code

			// Ensure that an item is selected
			if( lpNmListView->iItem >= 0 )
			{
				// An item is selected

				// Allocate string memory
				LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item text
				if( GetItemText( lpNmListView->iItem, DOWNLOAD_LIST_VIEW_WINDOW_CLASS_LOCAL_FILE_COLUMN_ID, lpszItemText ) )
				{
					// Successfully got item text

					// Call double click function
					( *lpDoubleClickFunction )( lpszItemText );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item text

				// Free string memory
				delete [] lpszItemText;

			} // End of an item is selected

			// Break out of switch
			break;

		} // End of a double click notification code
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for list view window notification code

	return bResult;

} // End of function DownloadListViewWindow::HandleNotifyMessage

/*
DownloadListViewWindow::
{
} // End of function DownloadListViewWindow::
*/