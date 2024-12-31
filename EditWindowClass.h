// EditWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define EDIT_WINDOW_CLASS_NAME													WC_EDIT
#define EDIT_WINDOW_CLASS_DEFAULT_TEXT											NULL
#define EDIT_WINDOW_CLASS_DEFAULT_MENU											NULL
#define EDIT_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE								0
#define EDIT_WINDOW_CLASS_DEFAULT_STYLE											( WS_CHILD | WS_VISIBLE | WS_BORDER )
#define EDIT_WINDOW_CLASS_DEFAULT_LEFT											CW_USEDEFAULT
#define EDIT_WINDOW_CLASS_DEFAULT_TOP											CW_USEDEFAULT
#define EDIT_WINDOW_CLASS_DEFAULT_WIDTH											CW_USEDEFAULT
#define EDIT_WINDOW_CLASS_DEFAULT_HEIGHT										CW_USEDEFAULT
#define EDIT_WINDOW_CLASS_DEFAULT_LP_PARAM										NULL

class EditWindow : public Window
{
public:
	EditWindow();
	~EditWindow();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = EDIT_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = EDIT_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = EDIT_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = EDIT_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = EDIT_WINDOW_CLASS_DEFAULT_LEFT, int nTop = EDIT_WINDOW_CLASS_DEFAULT_TOP, int nWidth = EDIT_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = EDIT_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = EDIT_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL HandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpUpdateFunction )( int nTextLength ) );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	
	void SelectText( int nStart = 0, int nEnd = -1 );

protected:

}; // End of class EditWindow
