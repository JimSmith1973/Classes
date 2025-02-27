// ListViewWindowClass.cpp

#include "ListViewWindowClass.h"

ListViewWindow::ListViewWindow()
{
	// Initialise member variables
	m_nColumnCount = 0;

} // End of function ListViewWindow::ListViewWindow
 
ListViewWindow::~ListViewWindow()
{
} // End of function ListViewWindow::~ListViewWindow

int ListViewWindow::AddColumn( LPCTSTR lpszColumnTitle, int nColumnWidth )
{
	int nResult;

	LVCOLUMN lvColumn;

	// Clear list view column structure
	::ZeroMemory( &lvColumn, sizeof( lvColumn ) );

	// Initialise list view column structure
	lvColumn.mask		= ( LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM );
	lvColumn.pszText	= ( LPTSTR )lpszColumnTitle;
	lvColumn.cchTextMax	= STRING_LENGTH;
	lvColumn.cx			= nColumnWidth;

	// Add column
	nResult = ::SendMessage( m_hWnd, LVM_INSERTCOLUMN, ( WPARAM )m_nColumnCount, ( LPARAM )&lvColumn );

	// Ensure that column was inserted
	if( nResult >= 0 )
	{
		// Successfully inserted column

		// Update global column count
		m_nColumnCount ++;

	} // End of successfully inserted column

	return nResult;

} // End of function ListViewWindow::AddColumn

int ListViewWindow::AddItem( LPCTSTR lpszItemText )
{
	int nResult;

	LVITEM lvItem;

	int nItemCount;

	// Clear list view item structure
	::ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Count items on list view window
	nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iItem		= nItemCount;
	lvItem.iSubItem		= 0;
	lvItem.pszText		= ( LPTSTR )lpszItemText;
	lvItem.cchTextMax	= STRING_LENGTH;

	// Add item to list view window
	nResult = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )&lvItem );

	return nResult;

} // End of function ListViewWindow::AddItem

int ListViewWindow::AddItemEx( LPCTSTR lpszItemText )
{
	int nResult;

	LVITEM lvItem;

	int nItemCount;

	// Clear list view item structure
	::ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Count items on list view window
	nItemCount = ::SendMessage( m_hWnd, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iItem		= nItemCount;
	lvItem.iSubItem		= 0;
	lvItem.pszText		= ( LPTSTR )lpszItemText;
	lvItem.cchTextMax	= STRING_LENGTH;

	// Add item to list view window
	nResult = ::SendMessage( m_hWnd, LVM_INSERTITEM, ( WPARAM )nItemCount, ( LPARAM )&lvItem );

	// Ensure that item was added to list view window
	if( nResult >= 0 )
	{
		// Successfully added item to list view window

		// Ensure that item is visible
		::SendMessage( m_hWnd, LVM_ENSUREVISIBLE , ( WPARAM )nResult, ( LPARAM )FALSE );

		// Update window
		::UpdateWindow( m_hWnd );

	} // End of successfully added item to list view window

	return nResult;

} // End of function ListViewWindow::AddItemEx

int ListViewWindow::AutoSizeAllColumns()
{
	int nResult = 0;

	int nWhichColumn;

	// Loop through all columns
	for( nWhichColumn = 0; nWhichColumn < m_nColumnCount; nWhichColumn ++ )
	{
		// Auto-size current column
		if( ::SendMessage( m_hWnd, LVM_SETCOLUMNWIDTH, ( WPARAM )nWhichColumn, ( LPARAM )LVSCW_AUTOSIZE_USEHEADER ) )
		{
			// Successfully auto-sized current column

			// Update return value
			nResult ++;

		} // End of successfully auto-sized current column
		else
		{
			// Unable to auto-size current column

			// Force exit from loop
			nWhichColumn = m_nColumnCount;

		} // End of unable to auto-size current column

	}; // End of loop through all columns

	return nResult;

} // End of function ListViewWindow::AutoSizeAllColumns

BOOL ListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, HMENU hMenu, DWORD dwExStyle, DWORD dwStyle, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( LIST_VIEW_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, hMenu, dwExStyle, dwStyle, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Set extended list view style
		::SendMessage( m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, ( WPARAM )0, ( LPARAM )LVS_EX_FULLROWSELECT );

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function ListViewWindow::Create

BOOL ListViewWindow::DeleteAllItems()
{
	// Delete all items
	return ::SendMessage( m_hWnd, LVM_DELETEALLITEMS, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function ListViewWindow::DeleteAllItems

int ListViewWindow::Find( LPCTSTR lpszItemText, int nStartAt )
{
	int nResult;

	LV_FINDINFO lvFindInfo;

	// Clear list view find information structure
	::ZeroMemory( &lvFindInfo, sizeof( lvFindInfo ) );

	// Initialise list view find information structure
	lvFindInfo.flags		= LVFI_STRING;
	lvFindInfo.psz			= ( LPTSTR )lpszItemText;
	//lvFindInfo.lParam		= NULL;
	//lvFindInfo.pt			= NULL;
	lvFindInfo.vkDirection	= VK_DOWN;

	// Do the find
	nResult = ::SendMessage( m_hWnd, LVM_FINDITEM, ( WPARAM )nStartAt, ( LPARAM )&lvFindInfo );

	return nResult;

} // End of function ListViewWindow::Find

int ListViewWindow::GetItemText( int nWhichItem, int nWhichSubItem, LPTSTR lpszItemText )
{
	int nResult;

	LVITEM lvItem;

	// Clear list view item structure
	::ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= nWhichSubItem;
	lvItem.pszText		= lpszItemText;
	lvItem.cchTextMax	= STRING_LENGTH;

	// Set item text
	nResult = ::SendMessage( m_hWnd, LVM_GETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem );

	return nResult;

} // End of function ListViewWindow::GetItemText

int ListViewWindow::GetSelectedItem()
{
	// Get selected item
	return ::SendMessage( m_hWnd, LVM_GETNEXTITEM, ( WPARAM )NULL, ( LPARAM )LVNI_FOCUSED );

} // End of function ListViewWindow::GetSelectedItem

BOOL ListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), PFNLVCOMPARE lpCompareFunction )
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
				if( GetItemText( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemText ) )
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

} // End of function ListViewWindow::HandleNotifyMessage

BOOL ListViewWindow::Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
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

} // End of function ListViewWindow::Move

int ListViewWindow::SetItemText( int nWhichItem, int nWhichSubItem, LPCTSTR lpszItemText )
{
	int nResult;

	LVITEM lvItem;

	// Clear list view item structure
	::ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iItem		= nWhichItem;
	lvItem.iSubItem		= nWhichSubItem;
	lvItem.pszText		= ( LPTSTR )lpszItemText;
	lvItem.cchTextMax	= STRING_LENGTH;

	// Set item text
	nResult = ::SendMessage( m_hWnd, LVM_SETITEM, ( WPARAM )nWhichItem, ( LPARAM )&lvItem );

	return nResult;

} // End of function ListViewWindow::SetItemText

/*
ListViewWindow::
{
} // End of function ListViewWindow::
*/