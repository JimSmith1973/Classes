// TreeViewWindowClass.cpp

#include "TreeViewWindowClass.h"

TreeViewWindow::TreeViewWindow()
{
} // End of function TreeViewWindow::TreeViewWindow
 
TreeViewWindow::~TreeViewWindow()
{
} // End of function TreeViewWindow::~TreeViewWindow

int TreeViewWindow::ActionChildItemText( BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) )
{
	int nResult = 0;

	HTREEITEM htiSelected;

	// Get selected item
	htiSelected = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )NULL );

	// Ensure that selected item was got
	if( htiSelected )
	{
		// Successfully got selected item

		// Action selected item
		nResult = ActionChildItemText( htiSelected, lpActionFunction );

	} // End of successfully got selected item

	return nResult;

} // End of function TreeViewWindow::ActionChildItemText

int TreeViewWindow::ActionChildItemText( HTREEITEM htiParent, BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) )
{
	int nResult;

	HTREEITEM htiCurrent;

	// Get first child item
	htiCurrent = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CHILD, ( LPARAM )htiParent );

	// Loop through all child items
	while( htiCurrent )
	{
		// Action current item
		if( ActionItemText( htiCurrent, lpActionFunction ) )
		{
			// Successfully actioned current item

			// Update return value
			nResult ++;

		} // End of successfully actioned current item

		// Get next child item
		htiCurrent = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_NEXT, ( LPARAM )htiCurrent );

	}; // End of loop through all child items

	return nResult;

} // End of function TreeViewWindow::ActionChildItemText

BOOL TreeViewWindow::ActionItemText( BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	HTREEITEM htiSelected;

	// Get selected item
	htiSelected = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )NULL );

	// Ensure that selected item was got
	if( htiSelected )
	{
		// Successfully got selected item

		// Action selected item
		bResult = ActionItemText( htiSelected, lpActionFunction );

	} // End of successfully got selected item

	return bResult;

} // End of function TreeViewWindow::ActionItemText

BOOL TreeViewWindow::ActionItemText( HTREEITEM htiCurrent, BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Allocate string memory
	LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get item text
	if( GetItemText( htiCurrent, lpszItemText ) )
	{
		// Successfully got item text

		// Action item
		bResult = ( *lpActionFunction )( lpszItemText );

	} // End of successfully got item text

	// Free string memory
	delete [] lpszItemText;

	return bResult;

} // End of function TreeViewWindow::ActionItemText

BOOL TreeViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( TREE_VIEW_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function TreeViewWindow::Create

HTREEITEM TreeViewWindow::FindItem( LPCTSTR lpszRequiredItemText, HTREEITEM htiParent )
{
	HTREEITEM htiResult = NULL;

	HTREEITEM htiCurrent;

	// Allocate string memory
	LPTSTR lpszCurrentItemText = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get first child item
	htiCurrent = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CHILD, ( LPARAM )htiParent );

	// Loop through all child items
	while( htiCurrent )
	{
		// Get current item text
		if( GetItemText( htiCurrent, lpszCurrentItemText ) )
		{
			// Successfully got current item text

			// See if this is the required item
			if( lstrcmpi( lpszCurrentItemText, lpszRequiredItemText ) == 0 )
			{
				// This is the required item

				// Update return value
				htiResult = htiCurrent;

				// Force exit from loop
				htiCurrent = NULL;

			} // End of this is the required item
			else
			{
				// This is not the required item

				// Get next child item
				htiCurrent = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_NEXT, ( LPARAM )htiCurrent );

			} // End of this is not the required item

		} // End of successfully got current item text
		else
		{
			// Unable to get current item text

			// Force exit from loop
			htiCurrent = NULL;

		} // End of unable to get current item text

	}; // End of loop through all child items

	// Free string memory
	delete [] lpszCurrentItemText;

	return htiResult;

} // End of function TreeViewWindow::FindItem

BOOL TreeViewWindow::GetItemPath( HTREEITEM htiCurrent, LPTSTR lpszItemPath, DWORD dwMaximumPathLength )
{
	BOOL bResult = TRUE; // Assume success

	TVITEM tvi;

	// Allocate string memory
	LPTSTR lpszItemText	= new char[ dwMaximumPathLength + sizeof( char ) ];
	LPTSTR lpszTemp		= new char[ dwMaximumPathLength + sizeof( char ) ];

	// Clear item path
	lpszItemPath[ 0 ] = ( char )NULL;

	// Clear tree view item structure
	::ZeroMemory( &tvi, sizeof( tvi ) );

	// Initialise tree view item structure
	tvi.mask		= TVIF_TEXT;
	tvi.hItem		= htiCurrent;
	tvi.pszText		= lpszItemText;
	tvi.cchTextMax	= dwMaximumPathLength;

	// Loop through parent items
	while( tvi.hItem )
	{
		// Get item text
		if( ::SendMessage( m_hWnd, TVM_GETITEM, ( WPARAM )NULL, ( LPARAM )&tvi ) )
		{
			// Successfully got item text

			// Copy item path into temporary string
			lstrcpy( lpszTemp, lpszItemPath );

			// Copy item text onto item path
			lstrcpy( lpszItemPath, lpszItemText );

			// See if temp string contains text
			if( lpszTemp[ 0 ] )
			{
				// Temp string contains text

				// Ensure that item path ends with a back-slash
				if( lpszItemPath[ lstrlen( lpszItemPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
				{
					// Item path does not end with a back-slash

					// Append a back-slash onto item path
					lstrcat( lpszItemPath, ASCII_BACK_SLASH_STRING );

				} // End of item path does not end with a back-slash

				// Append temp string onto item path
				lstrcat( lpszItemPath, lpszTemp );

			} // End of temp string contains text

			// Get parent item
			tvi.hItem = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_PARENT, ( LPARAM )tvi.hItem );

		} // End of successfully got item text
		else
		{
			// Unable to get item text

			// Update return value
			bResult = FALSE;

			// Force exit from loop
			tvi.hItem = NULL;

		} // End of unable to get item text

	}; // End of loop through parent items

	// Free string memory
	delete [] lpszItemText;
	delete [] lpszTemp;

	return bResult;

} // End of function TreeViewWindow::GetItemPath

BOOL TreeViewWindow::GetItemText( HTREEITEM htiCurrent, LPTSTR lpszItemText, DWORD dwMaximumTextLength )
{
	BOOL bResult = FALSE;

	TVITEM tvItem;

	// Clear tree view item structure
	::ZeroMemory( &tvItem, sizeof( tvItem ) );

	// Initialise tree view item structure
	tvItem.mask			= TVIF_TEXT;
	tvItem.pszText		= lpszItemText;
	tvItem.cchTextMax	= dwMaximumTextLength;
	tvItem.hItem		= htiCurrent;

	// Get item text
	bResult = ::SendMessage( m_hWnd, TVM_GETITEM, ( WPARAM )0, ( LPARAM )&tvItem );

	return bResult;

} // End of function TreeViewWindow::GetItemText

HTREEITEM TreeViewWindow::GetSelectedItem()
{
	// Get selected item
	return ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )NULL );

} // End of function TreeViewWindow::GetSelectedItem

BOOL TreeViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	LPNMTREEVIEW lpNmTreeView;

	// Store notify message handler
	lpNmTreeView = ( LPNMTREEVIEW )lParam;

	// Select notify message
	switch( lpNmTreeView->hdr.code )
	{
		case NM_DBLCLK:
		{
			// A double click notify message
			HTREEITEM htiSelected;

			// Get selected item
			htiSelected = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )NULL );

			// Ensure that selected item was got
			if( htiSelected )
			{
				// Successfully got selected item

				// Allocate string memory
				LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item text
				if( GetItemText( htiSelected, lpszItemText ) )
				{
					// Successfully got item text

					// Call double click function
					( *lpDoubleClickFunction )( lpszItemText );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item text

				// Free string memory
				delete [] lpszItemText;

			} // End of successfully got selected item

			// Break out of switch
			break;

		} // End of a double click notify message
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
			LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get item text
			if( GetItemText( lpNmTreeView->itemNew.hItem, lpszItemText ) )
			{
				// Successfully got item text

				// Call selection changed function
				( *lpSelectionChangedFunction )( lpszItemText );

				// Update return value
				bResult = TRUE;

			} // End of successfully got item text

			// Free string memory
			delete [] lpszItemText;

			// Break out of switch
			break;

		} // End of a selection changed notify message

	}; // End of selection for notify message

	return bResult;

} // End of function TreeViewWindow::HandleNotifyMessage

BOOL TreeViewWindow::HasChildren( HTREEITEM htiParent )
{
	BOOL bResult = FALSE;

	// Ensure that parent item is valid
	if( !( htiParent ) )
	{
		// Parent item is not valid

		// Get selected item as parent
		htiParent = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CARET, ( LPARAM )NULL );

	} // End of parent item is not valid

	// Ensure that parent item is valid
	if( htiParent )
	{
		// Parent item is valid
		HTREEITEM htiChild;

		// Get first child item
		htiChild = ( HTREEITEM )::SendMessage( m_hWnd, TVM_GETNEXTITEM, ( WPARAM )TVGN_CHILD, ( LPARAM )htiParent );

		// See if first child item was got
		if( htiChild )
		{
			// Successfully got first child item

			// Update return value
			bResult = TRUE;

		} // End of successfully got first child item

	} // End of parent item is valid

	return bResult;

} // End of function TreeViewWindow::HasChildren

HTREEITEM TreeViewWindow::InsertItem( LPCTSTR lpszItemText, HTREEITEM htiParent, HTREEITEM htiInsertAfter )
{
	HTREEITEM htiResult;

	TVINSERTSTRUCT tvInsert;

	// Clear tree view insert structure
	::ZeroMemory( &tvInsert, sizeof( tvInsert ) );

	// Initialise tree view insert structure
	tvInsert.item.mask		= TVIF_TEXT;
	tvInsert.item.pszText	= ( LPTSTR )lpszItemText;
	tvInsert.hParent		= htiParent;
	tvInsert.hInsertAfter	= htiInsertAfter;

	// Insert item
	htiResult = ( HTREEITEM )::SendMessage( m_hWnd, TVM_INSERTITEM, ( WPARAM )0, ( LPARAM )&tvInsert );

	return htiResult;

} // End of function TreeViewWindow::InsertItem

HTREEITEM TreeViewWindow::InsertItem( LPCTSTR lpszItemText, LPCTSTR lpszParentItemText, HTREEITEM htiInsertAfter )
{
	HTREEITEM htiResult = NULL;

	HTREEITEM htiParent;

	// Find parent item
	htiParent = FindItem( lpszParentItemText, TVI_ROOT );

	// Ensure that parent item was found
	if( !( htiParent ) )
	{
		// Unable to find parent item

		// Insert parent item
		htiParent = InsertItem( lpszParentItemText, TVI_ROOT, htiInsertAfter );

	} // End of unable to find parent item

	// Ensure that parent item is valid
	if( htiParent )
	{
		// Parent item is valid

		// Insert item
		htiResult = InsertItem( lpszItemText, htiParent, htiInsertAfter );

	} // End of parent item is valid

	return htiResult;

} // End of function TreeViewWindow::InsertItem

BOOL TreeViewWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function TreeViewWindow::Move

/*
TreeViewWindow::
{
} // End of function TreeViewWindow::
*/