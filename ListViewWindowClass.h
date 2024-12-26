// ListViewWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define LIST_VIEW_WINDOW_CLASS_NAME												WC_LISTVIEW
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU										NULL
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							LVS_EX_FULLROWSELECT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE									( WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT )
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT										CW_USEDEFAULT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP										CW_USEDEFAULT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH									CW_USEDEFAULT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT									CW_USEDEFAULT
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL
#define LIST_VIEW_WINDOW_CLASS_DEFAULT_COLUMN_WIDTH								100

class ListViewWindow : public Window
{
public:
	ListViewWindow();
	~ListViewWindow();

	int AddColumn( LPCTSTR lpszColumnTitle, int nColumnWidth = LIST_VIEW_WINDOW_CLASS_DEFAULT_COLUMN_WIDTH );

	int AddItem( LPCTSTR lpszItemText );

	int AutoSizeAllColumns();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT, DWORD dwExStyle = LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE, HMENU hMenu = LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU, int nLeft = LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

	int GetItemText( int nWhichItem, int nWhichSubItem, LPTSTR lpszItemText );

	int GetSelectedItem();

	BOOL HandleNotifyMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) = NULL );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

	int SetItemText( int nWhichItem, int nWhichSubItem, LPCTSTR lpszItemText );

protected:
	int m_nColumnCount;

}; // End of class ListViewWindow
