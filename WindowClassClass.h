// WindowClassClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define WINDOW_CLASS_CLASS_DEFAULT_MENU_NAME									NULL
#define WINDOW_CLASS_CLASS_DEFAULT_ICON_NAME									IDI_APPLICATION
#define WINDOW_CLASS_CLASS_DEFAULT_ICON											LoadIcon( NULL, WINDOW_CLASS_CLASS_DEFAULT_ICON_NAME )
#define WINDOW_CLASS_CLASS_DEFAULT_SMALL_ICON									LoadIcon( NULL, WINDOW_CLASS_CLASS_DEFAULT_ICON_NAME )
#define WINDOW_CLASS_CLASS_DEFAULT_BACKGROUND									( HBRUSH )( COLOR_WINDOW + 1 )
#define WINDOW_CLASS_CLASS_DEFAULT_CURSOR										LoadCursor( NULL, IDC_ARROW )
#define WINDOW_CLASS_CLASS_DEFAULT_STYLE										0
#define WINDOW_CLASS_CLASS_DEFAULT_CLS_EXTRA									0
#define WINDOW_CLASS_CLASS_DEFAULT_WND_EXTRA									0

#define WINDOW_CLASS_CLASS_UNABLE_TO_REGISTER_ERROR_MESSAGE						"Unable to Register Window Class"

class WindowClass
{
public:
	WindowClass();
	~WindowClass();

	WindowClass& operator = ( WNDCLASSEX wc );

	operator WNDCLASSEX();

	void Initialise( LPCTSTR lpszClassName, HINSTANCE hInstance, WNDPROC lpfnWndProc, LPCTSTR lpszMenuName = WINDOW_CLASS_CLASS_DEFAULT_MENU_NAME, HICON hIcon = WINDOW_CLASS_CLASS_DEFAULT_ICON, HICON hIconSm = WINDOW_CLASS_CLASS_DEFAULT_SMALL_ICON, HBRUSH hbrBackground = WINDOW_CLASS_CLASS_DEFAULT_BACKGROUND, HCURSOR hCursor = WINDOW_CLASS_CLASS_DEFAULT_CURSOR, UINT uStyle = WINDOW_CLASS_CLASS_DEFAULT_STYLE, int nClsExtra = WINDOW_CLASS_CLASS_DEFAULT_CLS_EXTRA, int nWndExtra = WINDOW_CLASS_CLASS_DEFAULT_WND_EXTRA );

	BOOL Register();

/*
UINT cbSize;
LPCSTR lpszClassName;
HINSTANCE hInstance;
WNDPROC lpfnWndProc;
LPCSTR lpszMenuName;
HICON hIcon;
HICON hIconSm;
HBRUSH hbrBackground;
HCURSOR hCursor;
UINT style;
int cbClsExtra;
int cbWndExtra;
*/
protected:
	WNDCLASSEX m_wc;

}; // End of class WindowClass
