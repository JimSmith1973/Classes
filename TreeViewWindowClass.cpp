// TreeViewWindowClass.cpp

#include "TreeViewWindowClass.h"

TreeViewWindow::TreeViewWindow()
{
} // End of function TreeViewWindow::TreeViewWindow
 
TreeViewWindow::~TreeViewWindow()
{
} // End of function TreeViewWindow::~TreeViewWindow

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