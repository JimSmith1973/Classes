// MenuClass.cpp

#include "MenuClass.h"

Menu::Menu()
{
	// Initialise member variables
	::ZeroMemory( &m_hMenu, sizeof( m_hMenu ) );

} // End of function Menu::Menu
 
Menu::~Menu()
{
	// Clear member variables
	::ZeroMemory( &m_hMenu, sizeof( m_hMenu ) );

} // End of function Menu::~Menu

Menu& Menu::operator = ( HMENU hMenu )
{
	// Update member variables
	m_hMenu = hMenu;

	return *this;

} // End of function Menu::operator =

BOOL Menu::operator == ( HMENU hMenu )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hMenu == m_hMenu )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Menu::operator ==

BOOL Menu::operator != ( HMENU hMenu )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hMenu != m_hMenu )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Menu::operator !=

Menu::operator HMENU()
{
	return m_hMenu;

} // End of function Menu::operator HMENU()

BOOL Menu::GetSystem( HWND hWnd, BOOL bRevert )
{
	BOOL bResult = FALSE;

	// Get system menu
	m_hMenu = ::GetSystemMenu( hWnd, bRevert );

	// Ensure that system menu was got
	if( m_hMenu )
	{
		// Successfully got system menu

		// Update return value
		bResult = TRUE;

	} // End of successfully got system menu

	return bResult;

} // End of function Menu::GetSystem

BOOL Menu::InsertItem( UINT uPosition, UINT uItemID, LPCTSTR lpszItemText )
{
	// Insert item
	return ::InsertMenu( m_hMenu, uPosition, MF_BYPOSITION, uItemID, lpszItemText );

} // End of function Menu::InsertItem

BOOL Menu::InsertSeparator( UINT uPosition )
{
	// Insert separator
	return ::InsertMenu( m_hMenu, uPosition, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

} // End of function Menu::InsertSeparator

BOOL Menu::Load( LPCTSTR lpszMenuName, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Load menu
	m_hMenu = ::LoadMenu( hInstance, lpszMenuName );

	// Ensure that menu was loaded
	if( m_hMenu )
	{
		// Successfully loaded menu

		// Update return value
		bResult = TRUE;

	} // End of successfully loaded menu

	return bResult;

} // End of function Menu::Load

BOOL Menu::TrackPopupMenu( int nWhichSubMenu, LPARAM lParam, HWND hWnd )
{
	// Track popup menu
	return ::TrackPopupMenu( GetSubMenu( m_hMenu, nWhichSubMenu ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWnd, NULL );

} // End of function Menu::TrackPopupMenu

/*
Menu::
{
} // End of function Menu::
*/