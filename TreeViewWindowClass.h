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

#define TREE_VIEW_WINDOW_CLASS_UNABLE_TO_GET_SELECTED_ITEM_ERROR_MESSAGE		"Unable to get selected tree item"

class TreeViewWindow : public Window
{
public:
	TreeViewWindow();
	~TreeViewWindow();

	int ActionChildItemText( BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) );

	int ActionChildItemText( HTREEITEM htiParent, BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) );

	BOOL ActionItemText( BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) );

	BOOL ActionItemText( HTREEITEM htiCurrent, BOOL( *lpActionFunction )( LPCTSTR lpszItemText ) );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = TREE_VIEW_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = TREE_VIEW_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = TREE_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = TREE_VIEW_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = TREE_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = TREE_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = TREE_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = TREE_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = TREE_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL DeleteAllChildItems( HTREEITEM htiParent );

	BOOL DeleteItem( HTREEITEM htiCurrent );

	BOOL ExpandItem( HTREEITEM htiCurrent, UINT uCode = TVE_EXPAND );

	HTREEITEM FindItem( LPCTSTR lpszRequiredItemText, HTREEITEM htiParent = TVI_ROOT );

	BOOL GetItemPath( HTREEITEM htiCurrent, LPTSTR lpszItemPath, DWORD dwMaximumPathLength = STRING_LENGTH );

	BOOL GetItemText( HTREEITEM htiCurrent, LPTSTR lpszItemText, DWORD dwMaximumTextLength = STRING_LENGTH );

	HTREEITEM GetSelectedItem();

	BOOL HandleNotifyMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPTSTR lpszItemText ) );

	BOOL HasChildren( HTREEITEM htiParent = NULL );

	HTREEITEM InsertItem( LPCTSTR lpszItemText, HTREEITEM htiParent = TVI_ROOT, HTREEITEM htiInsertAfter = TVI_SORT );

	HTREEITEM InsertItem( LPCTSTR lpszItemText, LPCTSTR lpszParentItemText, HTREEITEM htiInsertAfter = TVI_SORT );

	int Load( LPCTSTR lpszFilePath, HTREEITEM htiParent = TVI_ROOT, HTREEITEM htiInsertAfter = TVI_SORT );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

	int Save( LPCTSTR lpszFilePath, HTREEITEM htiParent = TVI_ROOT );

	BOOL SelectItem( HTREEITEM htiCurrent );

protected:

}; // End of class TreeViewWindow
