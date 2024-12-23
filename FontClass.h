// FontClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Font
{
public:
	Font();
	~Font();

	Font& operator = ( HFONT hFont );

	Font& operator = ( int nFontStockObject );

	BOOL operator == ( HFONT hFont );

	BOOL operator != ( HFONT hFont );

	operator HFONT();

	operator WPARAM();

protected:
	HFONT m_hFont;

}; // End of class Font
