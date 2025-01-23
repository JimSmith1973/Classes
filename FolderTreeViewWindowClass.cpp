// FolderTreeViewWindowClass.cpp

#include "FolderTreeViewWindowClass.h"

int FolderTreeViewWindow::AddDrives( HTREEITEM htiParent )
{
	int nResult = 0;

	// Allocate string memory
	LPTSTR lpszLogicalDrives = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get logical drive strings
	if( GetLogicalDriveStrings( STRING_LENGTH, lpszLogicalDrives ) != 0 )
	{
		// Successfully got logical drive strings
		HTREEITEM htiDrive;
		LPTSTR lpszCurrentDrive;

		TVINSERTSTRUCT tvInsert;

		// Clear tree view insert structure
		::ZeroMemory( &tvInsert, sizeof( tvInsert ) );

		// Initialise tree view insert structure
		tvInsert.item.mask		= TVIF_TEXT;
		tvInsert.hInsertAfter	= TVI_SORT;

		// Get first drive
		lpszCurrentDrive = lpszLogicalDrives;

		// Loop through all drives
		while( *lpszCurrentDrive )
		{
			// Update tree view insert structure for drive
			tvInsert.item.pszText	= lpszCurrentDrive;
			tvInsert.hParent		= htiParent;

			// Insert drive
			htiDrive = ( HTREEITEM )::SendMessage( m_hWnd, TVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&tvInsert );

			// Ensure that drive was inserted
			if( htiDrive )
			{
				// Successfully inserted drive

				// Update tree view insert structure for dummy sub-item
				tvInsert.hParent		= htiDrive;

				// Insert dummy sub-item
				::SendMessage( m_hWnd, TVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&tvInsert );

				// Get next drive
				lpszCurrentDrive += ( lstrlen( lpszCurrentDrive ) + sizeof( char ) );

			} // End of successfully inserted drive
			else
			{
				// Unable to insert drive

				// Force exit from loop
				lpszCurrentDrive[ 0 ] = ( char )NULL;

			} // End of unable to insert drive

		} // End of loop through all drives

	} // End of successfully got logical drive strings

	// Free string memory
	delete [] lpszLogicalDrives;

	return nResult;

} // End of function FolderTreeViewWindow::AddDrives

int FolderTreeViewWindow::AddSubFolders( HTREEITEM htiParent )
{
	int nResult = 0;

	// Allocate string memory
	LPTSTR lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get parent folder path
	if( GetItemPath( htiParent, lpszParentFolderPath ) )
	{
		// Successfully got parent folder path
		WIN32_FIND_DATA wfd;
		HANDLE hFind;

		// Allocate string memory
		LPTSTR lpszFullSearchPattern = new char[ STRING_LENGTH + sizeof( char ) ];

		// Ensure that parent folder path ends with a back-slash
		if( lpszParentFolderPath[ lstrlen( lpszParentFolderPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
		{
			// Parent folder path does not end with a back-slash

			// Append a back-slash onto parent folder path
			lstrcat( lpszParentFolderPath, ASCII_BACK_SLASH_STRING );

		} // End of parent folder path does not end with a back-slash

		// Copy parent folder path into full search pattern
		lstrcpy( lpszFullSearchPattern, lpszParentFolderPath );

		// Append all files filter onto full search pattern
		lstrcat( lpszFullSearchPattern, ALL_FILES_FILTER );

		// Find first item
		hFind = FindFirstFile( lpszFullSearchPattern, &wfd );

		// Ensure that first item was found
		if( hFind != INVALID_HANDLE_VALUE )
		{
			// Successfully found first item
			TVINSERTSTRUCT tvInsert;
			HTREEITEM htiFolder;

			// Clear tree view insert structure
			::ZeroMemory( &tvInsert, sizeof( tvInsert ) );

			// Initialise tree view insert structure
			tvInsert.item.mask		= TVIF_TEXT;
			tvInsert.hInsertAfter	= TVI_SORT;

			// Loop through all items
			do
			{
				// See if found item is a folder
				if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					// Found item is a folder

					// Ensure that found item is not dots
					if( wfd.cFileName[ 0 ] != ASCII_FULL_STOP_CHARACTER )
					{
						// Found item is not dots

						// Update tree view insert structure for folder
						tvInsert.hParent		= htiParent;
						tvInsert.item.pszText	= wfd.cFileName;

						// Insert folder
						htiFolder = ( HTREEITEM )::SendMessage( m_hWnd, TVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&tvInsert );

						// Ensure that folder was inserted
						if( htiFolder )
						{
							// Successfully inserted folder

							// Update tree view insert structure for dummy sub-item
							tvInsert.hParent		= htiFolder;

							// Insert dummy sub-item
							::SendMessage( m_hWnd, TVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&tvInsert );

						} // End of successfully inserted folder

					} // End of found item is not dots

				} // End of found item is a folder

			} while( FindNextFile( hFind, &wfd ) != 0 ); // End of loop through all items

			// Close file find
			FindClose( hFind );

		} // End of successfully found first item

		// Free string memory
		delete [] lpszFullSearchPattern;

	} // End of successfully got parent folder path

	// Free string memory
	delete [] lpszParentFolderPath;

	return nResult;

} // End of function FolderTreeViewWindow::AddSubFolders

BOOL FolderTreeViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( TreeViewWindow::Create( hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function FolderTreeViewWindow::Create

BOOL FolderTreeViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) )
{
	BOOL bResult = FALSE;

	LPNMTREEVIEW lpNmTreeView;

	// Store notify message handler
	lpNmTreeView = ( LPNMTREEVIEW )lParam;

	// Select notify message
	switch( lpNmTreeView->hdr.code )
	{
		case NM_RCLICK:
		{
			// A right click message
			HTREEITEM htiHighlighted;

			// Get highlighted tree item
			htiHighlighted = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_DROPHILITE, ( LPARAM )0 );

			// Ensure that highlighted tree item was got
			if( htiHighlighted )
			{
				// Successfully got highlighted tree item

				// Select highlighted tree item
				::SendMessage( m_hWnd, TVM_SELECTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )htiHighlighted );

			} // End of successfully got highlighted tree item

			// Break out of switch
			break;

		} // End of a right click message
		case TVN_ITEMEXPANDING:
		{
			// An item expanding notify message

			HTREEITEM htiExpanding;

			// Get expanding tree item
			htiExpanding = lpNmTreeView->itemNew.hItem;

			// Ensure that expanding tree item was got
			if( htiExpanding )
			{
				// Successfully got expanding tree item

				// Delete all child items of expanding item
				DeleteAllChildItems( htiExpanding );

				// Add sub-folders to expanding item
				AddSubFolders( htiExpanding );

				// Update return value
				bResult = TRUE;

			} // End of successfully got expanding tree item

			// Break out of switch
			break;

		} // End of an item expanding notify message
		case TVN_SELCHANGED:
		{
			// A selection changed notify message

			// Allocate string memory
			LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get item path
			if( GetItemPath( lpNmTreeView->itemNew.hItem, lpszItemPath ) )
			{
				// Successfully got item path

				// Call selection changed function
				( *lpSelectionChangedFunction )( lpszItemPath );

				// Update return value
				bResult = TRUE;

			} // End of successfully got item path

			// Free string memory
			delete [] lpszItemPath;

			// Break out of switch
			break;

		} // End of a selection changed notify message

	}; // End of selection for notify message

	return bResult;

} // End of function FolderTreeViewWindow::HandleNotifyMessage

BOOL FolderTreeViewWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
{
	BOOL bResult = FALSE;

	// Move window
	if( TreeViewWindow::Move( nLeft, nTop, nWidth, nHeight, bRepaint ) )
	{
		// Successfully moved window

		// Update return value
		bResult = TRUE;

	} // End of successfully moved window

	return bResult;

} // End of function FolderTreeViewWindow::Move

/*
FolderTreeViewWindow::
{
} // End of function FolderTreeViewWindow::
*/