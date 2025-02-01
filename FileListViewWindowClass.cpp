// FileListViewWindowClass.cpp

#include "FileListViewWindowClass.h"

FileListViewWindow::FileListViewWindow()
{
	// Allocate string memory
	m_lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear parent folder path
	m_lpszParentFolderPath[ 0 ] = ( char )NULL;

} // End of function FileListViewWindow::FileListViewWindow
 
FileListViewWindow::~FileListViewWindow()
{
	// Free string memory
	delete [] m_lpszParentFolderPath;

} // End of function FileListViewWindow::~FileListViewWindow

int FileListViewWindow::AddFiles( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter )
{
	int nResult = 0;

	WIN32_FIND_DATA wfd;
	HANDLE hFind;

	// Allocate string memory
	LPTSTR lpszFullSearchPattern = new char[ STRING_LENGTH ];

	// Store parent folder path
	lstrcpy( m_lpszParentFolderPath, lpszFolderPath );

	// Ensure that parent folder path ends with a back-slash
	if( m_lpszParentFolderPath[ lstrlen( m_lpszParentFolderPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
	{
		// Parent folder path does not end with a back-slash

		// Append a back-slash onto parent folder path
		lstrcat( m_lpszParentFolderPath, ASCII_BACK_SLASH_STRING );

	} // End of parent folder path does not end with a back-slash

	// Copy parent folder path into full search pattern
	lstrcpy( lpszFullSearchPattern, m_lpszParentFolderPath );

	// Append file filter onto full search pattern
	lstrcat( lpszFullSearchPattern, lpszFileFilter );

	// Find first item
	hFind = FindFirstFile( lpszFullSearchPattern, &wfd );
	
	// Ensure that first item was found
	if( hFind != INVALID_HANDLE_VALUE )
	{
		// Successfully found first item
		LVITEM lvItem;
		int nItemCount;
		int nWhichItem;

		// Clear list view item structure
		::ZeroMemory( &lvItem, sizeof( lvItem ) );

		// Count items on list view window
		nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Initialise list view item structure
		lvItem.mask			= LVIF_TEXT;
		lvItem.iItem		= nItemCount;
		lvItem.cchTextMax	= STRING_LENGTH;

		// Loop through all items
		do
		{
			// Ensure that found item is a file
			if( !( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			{
				// Found item is a file

				// Update list view item structure for file
				lvItem.iSubItem		= FILE_LIST_VIEW_WINDOW_CLASS_NAME_COLUMN_ID;
				lvItem.pszText		= wfd.cFileName;

				// Add file to list view window
				nWhichItem = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );
				
				// Ensure that file was added to list view window
				if( nWhichItem >= 0 )
				{
					// Successfully added file to list view window

					// Update return value
					nResult ++;

				} // End of successfully added file to list view window

			} // End of found item is a file

		} while( FindNextFile( hFind, &wfd ) ); 

		// Close file find
		FindClose( hFind );

	} // End of successfully found first item

	// Free string memory
	delete [] lpszFullSearchPattern;

	return nResult;

} // End of function FileListViewWindow::AddSubFolders

BOOL FileListViewWindow::FileListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
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

int FileListViewWindow::GetItemPath( int nWhichItem, LPTSTR lpszItemPath )
{
	int nResult;

	// Copy parent folder path into item path
	lstrcpy( lpszItemPath, m_lpszParentFolderPath );

	// Append item name onto item path
	nResult = GetItemText( nWhichItem, FILE_LIST_VIEW_WINDOW_CLASS_NAME_COLUMN_ID, ( lpszItemPath + lstrlen( lpszItemPath ) ) );

	return nResult;

} // End of function FileListViewWindow::GetItemPath

int FileListViewWindow::GetItemPath(LPTSTR lpszItemPath )
{
	int nResult;

	int nWhichItem;

	// Get selected item
	nWhichItem = ::SendMessage( m_hWnd, LVM_GETNEXTITEM, ( WPARAM )NULL, ( LPARAM )LVNI_FOCUSED );

	// Get item path
	nResult = GetItemPath( nWhichItem, lpszItemPath );

	return nResult;

} // End of function FileListViewWindow::GetItemPath

BOOL FileListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPCTSTR lpszItemPath ), void( *lpDoubleClickFunction )( LPCTSTR lpszItemPath ) )
{
	BOOL bResult = FALSE;

	LPNMLISTVIEW lpNmListView;

	// Store notify message handler
	lpNmListView = ( LPNMLISTVIEW )lParam;

	// Select notify message
	switch( lpNmListView->hdr.code )
	{
		case NM_DBLCLK:
		{
			// A double click notification code

			// See if selection has changed
			if( ( lpNmListView->uNewState ^ lpNmListView->uOldState ) & LVIS_SELECTED )
			{
				// Selection has changed

				// Allocate string memory
				LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item path
				if( GetItemPath( lpNmListView->iItem, lpszItemPath ) )
				{
					// Successfully got item path

					// Call double click function
					( *lpDoubleClickFunction )( lpszItemPath );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item path

				// Free string memory
				delete [] lpszItemPath;

			} // End of selection has changed

			// Break out of switch
			break;

		} // End of a double click notification code
		case TVN_ITEMEXPANDING:
		{
			// An item expanding notify message

			// Break out of switch
			break;

		} // End of an item expanding notify message
		case LVN_ITEMCHANGED:
		{
			// A list view window item changed notification code

			// See if selection has changed
			if( ( lpNmListView->uNewState ^ lpNmListView->uOldState ) & LVIS_SELECTED )
			{
				// Selection has changed

				// Allocate string memory
				LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item path
				if( GetItemPath( lpNmListView->iItem, lpszItemPath ) )
				{
					// Successfully got item path

					// Call selection changed function
					( *lpSelectionChangedFunction )( lpszItemPath );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item path

				// Free string memory
				delete [] lpszItemPath;

			} // End of selection has changed

			// Break out of switch
			break;

		} // End of a list view window item changed notification code

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