// WindowClassClass.cpp

#include "WindowClassClass.h"

WindowClass::WindowClass()
{
	// Initialise member variables
	ZeroMemory( &m_wc, sizeof( m_wc ) );

} // End of function WindowClass::WindowClass
 
WindowClass::~WindowClass()
{
	// Clear member variables
	ZeroMemory( &m_wc, sizeof( m_wc ) );

} // End of function WindowClass::~WindowClass

WindowClass& WindowClass::operator = ( WNDCLASSEX wc )
{
	// Update member variables
	m_wc = wc;

	return *this;

} // End of function WindowClass::operator =

WindowClass::operator WNDCLASSEX()
{
	return m_wc;

} // End of function WindowClass::operator WNDCLASSEX()

void WindowClass::Initialise( LPCTSTR lpszClassName, HINSTANCE hInstance, WNDPROC lpfnWndProc, LPCTSTR lpszMenuName, HICON hIcon, HICON hIconSm, HBRUSH hbrBackground, HCURSOR hCursor, UINT uStyle, int nClsExtra, int nWndExtra )
{
	// Clear window class structure
	ZeroMemory( &m_wc, sizeof( m_wc ) );

	// Initialise window class structure
	m_wc.cbSize			= sizeof( WNDCLASSEX );
	m_wc.lpszClassName	= lpszClassName;
	m_wc.hInstance		= hInstance;
	m_wc.lpfnWndProc	= lpfnWndProc;
	m_wc.lpszMenuName	= lpszMenuName;
	m_wc.hIcon			= hIcon;
	m_wc.hIconSm		= hIconSm;
	m_wc.hbrBackground	= hbrBackground;
	m_wc.hCursor		= hCursor;
	m_wc.style			= uStyle;
	m_wc.cbClsExtra		= nClsExtra;
	m_wc.cbWndExtra		= nWndExtra;

} // End of function WindowClass::Initialise

BOOL WindowClass::Register()
{
	BOOL bResult = FALSE;

	// Register window class
	if( RegisterClassEx( &m_wc ) )
	{
		// Successfully registered window class

		// Update return value
		bResult = TRUE;

	} // End of successfully registered window class

	return bResult;

} // End of function WindowClass::Register

/*
WindowClass::
{
} // End of function WindowClass::
*/