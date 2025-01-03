// StringClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class String
{
public:
	String();
	String( LPCTSTR lpszBuffer );
	~String();

	String& operator = ( LPCTSTR lpszBuffer );

	BOOL operator == ( LPCTSTR lpszBuffer );

	BOOL operator != ( LPCTSTR lpszBuffer );

	String& operator += ( char cAppend );

	String& operator += ( LPCTSTR lpszAppend );
	
	String operator + ( LPCTSTR lpszAdd );

	operator LPTSTR();

	int Display( HWND hWnd = NULL, LPCTSTR lpszCaption = INFORMATION_MESSAGE_CAPTION, UINT uType = MB_OK );

protected:
	LPTSTR m_lpszBuffer;
	DWORD m_dwBufferLength;

}; // End of class String
