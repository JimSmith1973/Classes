// FileListViewWindowClass.cpp

#include "FileListViewWindowClass.h"

FileListViewWindow::FileListViewWindow()
{
	// Initialise member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

	// Allocate string memory
	m_lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear parent folder path
	m_lpszParentFolderPath[ 0 ] = ( char )NULL;

} // End of function FileListViewWindow::FileListViewWindow
 
FileListViewWindow::~FileListViewWindow()
{
	// Clear member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

	// Free string memory
	delete [] m_lpszParentFolderPath;

} // End of function FileListViewWindow::~FileListViewWindow

FileListViewWindow& FileListViewWindow::operator = ( HWND hWnd )
{
	// Update member variables
	m_hWnd = hWnd;

	return *this;

} // End of function FileListViewWindow::operator =

BOOL FileListViewWindow::operator == ( HWND hWnd )
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

} // End of function FileListViewWindow::operator ==

BOOL FileListViewWindow::operator != ( HWND hWnd )
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

} // End of function FileListViewWindow::operator !=

FileListViewWindow::operator HWND()
{
	return m_hWnd;

} // End of function FileListViewWindow::operator HWND()

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
		SYSTEMTIME stModified;

		// Clear list view item structure
		::ZeroMemory( &lvItem, sizeof( lvItem ) );

		// Count items on list view window
		nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Initialise list view item structure
		lvItem.mask			= LVIF_TEXT;
		lvItem.iItem		= nItemCount;
		lvItem.cchTextMax	= STRING_LENGTH;

		// Allocate string memory
		LPTSTR lpszModified = new char[ STRING_LENGTH ];

		// Loop through all items
		do
		{
			// Ensure that found item is a file
			if( !( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			{
				// Found item is a file

				// Update list view item structure for file name
				lvItem.iSubItem		= FILE_LIST_VIEW_WINDOW_CLASS_NAME_COLUMN_ID;
				lvItem.pszText		= wfd.cFileName;

				// Add file to list view window
				nWhichItem = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );

				// Ensure that file was added to list view window
				if( nWhichItem >= 0 )
				{
					// Successfully added file to list view window

					// Get modified time
					if( FileTimeToSystemTime( ( &( wfd.ftLastWriteTime ) ), &stModified ) )
					{
						// Successfully got modified time

						// Format modified text
						wsprintf( lpszModified, FILE_LIST_VIEW_WINDOW_CLASS_MODIFIED_TEXT_FORMAT_STRING, stModified.wYear, stModified.wMonth, stModified.wDay, stModified.wHour, stModified.wMinute, stModified.wSecond );

						// Update list view item structure for file
						lvItem.iSubItem		= FILE_LIST_VIEW_WINDOW_CLASS_MODIFIED_COLUMN_ID;
						lvItem.pszText		= lpszModified;

						// Add file to list view window
						::SendMessage( m_hWnd, LVM_SETITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );

					} // End of successfully got modified time

					// Update return value
					nResult ++;

				} // End of successfully added file to list view window

			} // End of found item is a file

		} while( FindNextFile( hFind, &wfd ) ); 

		// Close file find
		FindClose( hFind );

		// Free string memory
		delete [] lpszModified;

	} // End of successfully found first item

	// Free string memory
	delete [] lpszFullSearchPattern;

	return nResult;

} // End of function FileListViewWindow::AddFiles

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

int FileListViewWindow::GetItemPath( int nWhichItem, LPTSTR lpszItemPath )
{
	int nResult;

	LVITEM lvItem;

	// Copy parent folder path into item path
	lstrcpy( lpszItemPath, m_lpszParentFolderPath );

	// Clear list view item structure
	::ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= FILE_LIST_VIEW_WINDOW_CLASS_NAME_COLUMN_ID;
	lvItem.pszText		= ( lpszItemPath + lstrlen( lpszItemPath ) );
	lvItem.cchTextMax	= STRING_LENGTH;

	// Set item text
	nResult = ::SendMessage( m_hWnd, LVM_GETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem );

	return nResult;

} // End of function FileListViewWindow::GetItemPath

BOOL FileListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), PFNLVCOMPARE lpCompareFunction )
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
		case NM_DBLCLK:
		{
			// A double click notification code

			// Ensure that an item is selected
			if( lpNmListView->iItem >= 0 )
			{
				// An item is selected

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

} // End of function FileListViewWindow::HandleNotifyMessage

int FileListViewWindow::Populate( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter )
{
	int nResult;

	// Delete all items from list view window
	DeleteAllItems();

	// Add files to list view window
	nResult = AddFiles( lpszFolderPath, lpszFileFilter );

	// Auto-size all list wiew window columns
	AutoSizeAllColumns();

	return nResult;

} // End of function FileListViewWindow::Populate

/*
FileListViewWindow::
{
} // End of function FileListViewWindow::
*/