// TemplateClass.cpp

#include "TemplateClass.h"

Template::Template()
{
	// Initialise member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function Template::Template
 
Template::~Template()
{
	// Clear member variables
	::ZeroMemory( &m_hWnd, sizeof( m_hWnd ) );

} // End of function Template::~Template

Template& Template::operator = ( HWND hWnd )
{
	// Update member variables
	m_hWnd = hWnd;

	return *this;

} // End of function Template::operator =

BOOL Template::operator == ( HWND hWnd )
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

} // End of function Template::operator ==

BOOL Template::operator != ( HWND hWnd )
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

} // End of function Template::operator !=

Template::operator HWND()
{
	return m_hWnd;

} // End of function Template::operator HWND()

/*
Template::
{
} // End of function Template::
*/