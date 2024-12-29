// WindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define WINDOW_CLASS_DEFAULT_TITLE												NULL
#define WINDOW_CLASS_DEFAULT_EXTENDED_STYLE										( WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES )
#define WINDOW_CLASS_DEFAULT_STYLE												WS_OVERLAPPEDWINDOW
#define WINDOW_CLASS_DEFAULT_MENU												NULL
#define WINDOW_CLASS_DEFAULT_LEFT												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_TOP												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_WIDTH												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_HEIGHT												CW_USEDEFAULT
#define WINDOW_CLASS_DEFAULT_PARAM												NULL

#define WINDOW_CLASS_DEFAULT_MINIMUM_WIDTH										320
#define WINDOW_CLASS_DEFAULT_MINIMUM_HEIGHT										200

#define WINDOW_CLASS_UNABLE_TO_CREATE_WINDOW_ERROR_MESSAGE						"Unable to Create Window"

class Window
{
public:
	Window();
	~Window();

	Window& operator = ( HWND hWnd );

	BOOL operator == ( HWND hWnd );

	BOOL operator != ( HWND hWnd );

	operator HWND();

	BOOL Create( LPCTSTR lpszClassName, HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowTitle = WINDOW_CLASS_DEFAULT_TITLE, DWORD dwExStyle = WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = WINDOW_CLASS_DEFAULT_STYLE, HMENU hMenu = WINDOW_CLASS_DEFAULT_MENU, int nLeft = WINDOW_CLASS_DEFAULT_LEFT, int nTop = WINDOW_CLASS_DEFAULT_TOP, int nWidth = WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = WINDOW_CLASS_DEFAULT_PARAM );

	LRESULT DefaultProcedure( UINT uMessage, WPARAM wParam, LPARAM lParam );

	BOOL Destroy();

	BOOL Enable( BOOL bEnable );

	BOOL GetClientRect( LPRECT lpRect );

	HMENU GetSystemMenu( BOOL bRevert = FALSE );

	int GetText( LPTSTR lpszText, DWORD dwMaximumTextLength = STRING_LENGTH );

	DWORD GetTextLength();

	BOOL GetWindowRect( LPRECT lpRect );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

	LRESULT SendMessage( UINT uMessage, WPARAM wParam, LPARAM lParam );

	HWND SetFocus();

	void SetFont( HFONT hFont );

	BOOL SetText( LPCTSTR lpszText );

	BOOL Show( int nCmdShow );

	BOOL Update();

protected:
	HWND m_hWnd;

}; // End of class Window
