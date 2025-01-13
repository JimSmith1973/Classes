// ClipboardClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Clipboard
{
public:
	Clipboard();
	~Clipboard();

	BOOL GetText( LPTSTR lpszText );

	DWORD GetTextLength();

	BOOL SetText( LPCTSTR lpszText );

protected:

}; // End of class Clipboard
