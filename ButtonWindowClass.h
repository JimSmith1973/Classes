// ButtonWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define BUTTON_WINDOW_CLASS_NAME												WC_BUTTON
#define BUTTON_WINDOW_DEFAULT_ID												WM_USER
#define BUTTON_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE								0
#define BUTTON_WINDOW_CLASS_DEFAULT_STYLE										( WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | BS_VCENTER )
#define BUTTON_WINDOW_CLASS_DEFAULT_LEFT										CW_USEDEFAULT
#define BUTTON_WINDOW_CLASS_DEFAULT_TOP											CW_USEDEFAULT
#define BUTTON_WINDOW_CLASS_DEFAULT_WIDTH										CW_USEDEFAULT
#define BUTTON_WINDOW_CLASS_DEFAULT_HEIGHT										CW_USEDEFAULT
#define BUTTON_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class ButtonWindow : public Window
{
public:
	ButtonWindow();
	~ButtonWindow();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText, int nID, DWORD dwExStyle = BUTTON_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = BUTTON_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = BUTTON_WINDOW_CLASS_DEFAULT_LEFT, int nTop = BUTTON_WINDOW_CLASS_DEFAULT_TOP, int nWidth = BUTTON_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = BUTTON_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = BUTTON_WINDOW_CLASS_DEFAULT_LP_PARAM );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

protected:

}; // End of class ButtonWindow
