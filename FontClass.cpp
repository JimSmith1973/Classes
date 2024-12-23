// FontClass.cpp

#include "FontClass.h"

Font::Font()
{
	// Initialise member variables
	::ZeroMemory( &m_hFont, sizeof( m_hFont ) );

} // End of function Font::Font
 
Font::~Font()
{
	// Clear member variables
	::ZeroMemory( &m_hFont, sizeof( m_hFont ) );

} // End of function Font::~Font

Font& Font::operator = ( HFONT hFont )
{
	// Update member variables
	m_hFont = hFont;

	return *this;

} // End of function Font::operator =

Font& Font::operator = ( int nFontStockObject )
{
	// Update member variables
	m_hFont = ( HFONT )::GetStockObject( nFontStockObject );

	return *this;

} // End of function Font::operator =

BOOL Font::operator == ( HFONT hFont )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hFont == m_hFont )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Font::operator ==

BOOL Font::operator != ( HFONT hFont )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hFont != m_hFont )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Font::operator !=

Font::operator HFONT()
{
	return m_hFont;

} // End of function Font::operator HFONT()

Font::operator WPARAM()
{
	return ( WPARAM )m_hFont;

} // End of function Font::operator WPARAM()

/*
Font::
{
} // End of function Font::
*/