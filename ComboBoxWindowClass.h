// ComboBoxWindowClass.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include <windows.h>

#include "WindowClass.h"

#define COMBO_BOX_WINDOW_CLASS_NAME												WC_COMBOBOX
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_ID										WM_USER
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_STYLE									( WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST )
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_LEFT										CW_USEDEFAULT
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_TOP										CW_USEDEFAULT
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_WIDTH									CW_USEDEFAULT
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_HEIGHT									CW_USEDEFAULT
#define COMBO_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

#define COMBO_BOX_WINDOW_CLASS_FIND_ALL_ITEMS									-1

#define COMBO_BOX_WINDOW_CLASS_UNABLE_TO_SAVE_WARNING_MESSAGE					"Unable to save combo box window.\r\n\r\nDo you want to close?"

class ComboBoxWindow : public Window
{
public:
	ComboBoxWindow();
	~ComboBoxWindow();

	int AddItem( LPCTSTR lpszItemText );

	int AddString( LPCTSTR lpszString );

	int AddText( LPCTSTR lpszText );

	int AddUniqueItem( LPCTSTR lpszItemText );

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = COMBO_BOX_WINDOW_CLASS_DEFAULT_TEXT, int nID = COMBO_BOX_WINDOW_CLASS_DEFAULT_ID, DWORD dwExStyle = COMBO_BOX_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = COMBO_BOX_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = COMBO_BOX_WINDOW_CLASS_DEFAULT_LEFT, int nTop = COMBO_BOX_WINDOW_CLASS_DEFAULT_TOP, int nWidth = COMBO_BOX_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = COMBO_BOX_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = COMBO_BOX_WINDOW_CLASS_DEFAULT_LP_PARAM );

	int FindItem( LPCTSTR lpszRequiredItemText, int nFirstItem = COMBO_BOX_WINDOW_CLASS_FIND_ALL_ITEMS );

	BOOL HandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpSelectionChangedFunction )( LPTSTR lpszItemText ) );

	BOOL Load( LPCTSTR lpszFileName );

	BOOL Move( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

	BOOL Save( LPCTSTR lpszFileName );

	int SelectItem( int nWhichItem );

protected:

}; // End of class ComboBoxWindow
