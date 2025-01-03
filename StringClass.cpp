// StringClass.cpp

#include "StringClass.h"

String::String()
{
	// Initialise buffer length
	m_dwBufferLength = 0;

	// Allocate string memory
	m_lpszBuffer = new char[ m_dwBufferLength + sizeof( char ) ];

	// Initialise buffer
	m_lpszBuffer[ m_dwBufferLength ] = ( char )NULL;

} // End of function String::String

String::String( LPCTSTR lpszBuffer )
{
	// Initialise buffer length
	m_dwBufferLength = lstrlen( lpszBuffer );

	// Allocate string memory
	m_lpszBuffer = new char[ m_dwBufferLength + sizeof( char ) ];

	// Initialise buffer
	lstrcpy( m_lpszBuffer, lpszBuffer );

} // End of function String::String

String::~String()
{
	// Free string memory
	delete [] m_lpszBuffer;

} // End of function String::~String

String& String::operator = ( LPCTSTR lpszBuffer )
{
	// Free string memory
	delete [] m_lpszBuffer;

	// Initialise buffer length
	m_dwBufferLength = lstrlen( lpszBuffer );

	// Allocate string memory
	m_lpszBuffer = new char[ m_dwBufferLength + sizeof( char ) ];

	// Initialise buffer
	lstrcpy( m_lpszBuffer, lpszBuffer );

	return *this;

} // End of function String::operator =

BOOL String::operator == ( LPCTSTR lpszBuffer )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( lstrcmp( lpszBuffer, m_lpszBuffer ) == 0 )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function String::operator ==

BOOL String::operator != ( LPCTSTR lpszBuffer )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( lstrcmp( lpszBuffer, m_lpszBuffer ) != 0 )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function String::operator !=

String::operator LPTSTR()
{
	return m_lpszBuffer;

} // End of function String::operator LPTSTR()

int String::Display( HWND hWnd, LPCTSTR lpszCaption, UINT uType )
{
	// Display string
	return ::MessageBox( hWnd, m_lpszBuffer, lpszCaption, uType );

} // End of function String::Display

/*
String::
{
} // End of function String::
*/