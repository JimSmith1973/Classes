// ListBoxWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define LIST_BOX_WINDOW_CLASS_NAME												WC_LISTBOX
#define LIST_BOX_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define LIST_BOX_WINDOW_CLASS_DEFAULT_MENU										NULL
#define LIST_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define LIST_BOX_WINDOW_CLASS_DEFAULT_STYLE										( WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define LIST_BOX_WINDOW_CLASS_DEFAULT_LEFT										CW_USEDEFAULT
#define LIST_BOX_WINDOW_CLASS_DEFAULT_TOP										CW_USEDEFAULT
#define LIST_BOX_WINDOW_CLASS_DEFAULT_WIDTH										CW_USEDEFAULT
#define LIST_BOX_WINDOW_CLASS_DEFAULT_HEIGHT									CW_USEDEFAULT
#define LIST_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class ListBoxWindow : public Window
{
public:
	ListBoxWindow();
	~ListBoxWindow();

	int AddString( LPCTSTR lpszString );

	int AddText( LPCTSTR lpszText );

	int AddTextEx( LPCTSTR lpszText );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = LIST_BOX_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = LIST_BOX_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = LIST_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = LIST_BOX_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = LIST_BOX_WINDOW_CLASS_DEFAULT_LEFT, int nTop = LIST_BOX_WINDOW_CLASS_DEFAULT_TOP, int nWidth = LIST_BOX_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = LIST_BOX_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = LIST_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM );

	int GetCurrentSelection();

	int GetText( int nWhichItem, LPTSTR lpszText );

	BOOL HandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ), void( *lpDoubleClickFunction )( LPTSTR lpszItemText ) );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

protected:

}; // End of class ListBoxWindow
