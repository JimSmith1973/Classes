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

} // End of function TreeViewWindow::InsertItem

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