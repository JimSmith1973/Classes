// TreeViewWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define TREE_VIEW_WINDOW_CLASS_NAME												WC_TREEVIEW
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_MENU										NULL
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_STYLE									( WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT )
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_LEFT										CW_USEDEFAULT
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_TOP										CW_USEDEFAULT
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_WIDTH									CW_USEDEFAULT
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT									CW_USEDEFAULT
#define TREE_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class TreeViewWindow : public Window
{
public:
	TreeViewWindow();
	~TreeViewWindow();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = TREE_VIEW_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = TREE_VIEW_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = TREE_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = TREE_VIEW_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = TREE_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = TREE_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = TREE_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = TREE_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = TREE_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

	HTREEITEM FindItem( LPCTSTR lpszRequiredItemText, HTREEITEM htiParent = TVI_ROOT );

	BOOL GetItemText( HTREEITEM htiCurrent, LPTSTR lpszItemText, DWORD dwMaximumTextLength = STRING_LENGTH );

	BOOL HandleNotifyMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPTSTR lpszItemText ) );

	HTREEITEM InsertItem( LPCTSTR lpszItemText, HTREEITEM htiParent = TVI_ROOT, HTREEITEM htiInsertAfter = TVI_SORT );

	HTREEITEM InsertItem( LPCTSTR lpszItemText, LPCTSTR lpszParentItemText, HTREEITEM htiInsertAfter = TVI_SORT );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

protected:

}; // End of class TreeViewWindow
