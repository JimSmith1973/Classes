// WindowClass.cpp

#include "WindowClass.h"

Window::Window()
{
	// Initialise member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function Window::Window
 
Window::~Window()
{
	// Clear member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function Window::~Window

Window& Window::operator = ( HWND hWnd )
{
	// Update member variables
	m_hWnd = hWnd;

	return *this;

} // End of function Window::operator =

BOOL Window::operator == ( HWND hWnd )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hWnd == m_hWnd )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Window::operator ==

BOOL Window::operator != ( HWND hWnd )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hWnd != m_hWnd )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Window::operator !=

Window::operator HWND()
{
	return m_hWnd;

} // End of function Window::operator HWND()

BOOL Window::Create( LPCTSTR lpszClassName, HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowTitle, DWORD dwExStyle, DWORD dwStyle, HMENU hMenu, int nLeft, int nTop, int nWidth, int nHeight, LPVOID lpParam )
{
	BOOL bResult = FALSE;

	// Create window
	m_hWnd = ::CreateWindowEx( dwExStyle, lpszClassName, lpszWindowTitle, dwStyle, nLeft, nTop, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam );
	
	// Ensure that window was created
	if( m_hWnd )
	{
		// Successfully created window

		// Update return value
		bResult = TRUE;

	} // End of successfully created window

	return bResult;

} // End of function Window::Create

HMENU Window::GetSystemMenu( BOOL bRevert )
{
	// Get system menu
	return ::GetSystemMenu( m_hWnd, bRevert );

} // End of function Window::GetSystemMenu

BOOL Window::Show( int nCmdShow )
{
	// Show window
	return ::ShowWindow( m_hWnd, nCmdShow );

} // End of function Window::Show

BOOL Window::Update()
{
	// Update window
	return ::UpdateWindow( m_hWnd );

} // End of function Window::Update

/*
Window::
{
} // End of function Window::
*/