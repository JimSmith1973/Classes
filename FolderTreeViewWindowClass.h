// FolderTreeViewWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "TreeViewWindowClass.h"

#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_TEXT								NULL
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_MENU								NULL
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE					0
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_STYLE								( WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT )
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_LEFT								CW_USEDEFAULT
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_TOP								CW_USEDEFAULT
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_WIDTH								CW_USEDEFAULT
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT							CW_USEDEFAULT
#define FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM							NULL

class FolderTreeViewWindow : public TreeViewWindow
{
public:
	int AddDrives( HTREEITEM htiParent = TVI_ROOT );

	int AddSubFolders( HTREEITEM htiParent );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = FOLDER_TREE_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL HandleNotifyMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR ) = NULL );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

protected:

}; // End of class FolderTreeViewWindow
