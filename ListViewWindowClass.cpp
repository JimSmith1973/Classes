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

BOOL ListViewWindow::Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, DWORD dwExStyle, DWORD dwStyle, HMENU hMenu, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	if( Window::Create( LIST_VIEW_WINDOW_CLASS_NAME, hWndParent, hInstance, lpszWindowText, dwExStyle, dwStyle, hMenu, nLeft, nTop, nWidth, nHeight, lpParam ) )
	{
		// Successfully created window

		// Set extended list view style
		::SendMessage( m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, ( WPARAM )0, ( LPARAM )LVS_EX_FULLROWSELECT );

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function ListViewWindow::Create

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

BOOL ListViewWindow::HandleNotifyMessage( WPARAM, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) )
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