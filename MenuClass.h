// MenuClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Menu
{
public:
	Menu();
	~Menu();

	Menu& operator = ( HMENU hMenu );

	BOOL operator == ( HMENU hMenu );

	BOOL operator != ( HMENU hMenu );

	operator HMENU();

	BOOL GetSystem( HWND hWnd, BOOL bRevert = FALSE );

	BOOL InsertItem( UINT uPosition, UINT uItemID, LPCTSTR lpszItemText );

	BOOL InsertSeparator( UINT uPosition );

	BOOL Load( LPCTSTR lpszMenuName, HINSTANCE hInstance = NULL );

	BOOL TrackPopupMenu( int nWhichSubMenu, LPARAM lParam, HWND hWnd );

protected:
	HMENU m_hMenu;

}; // End of class Menu