// BitmapClass.h

#pragma once

#include <windows.h>
#include <olectl.h>
#include <ole2.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define BITMAP_CLASS_UNABLE_TO_CREATE_BITMAP_ERROR_MESSAGE						"Unable to Create Bitmap"
#define BITMAP_CLASS_UNABLE_TO_LOAD_BITMAP_ERROR_MESSAGE_FORMAT_STRING			"Unable to Load Bitmap '%s'"

class Bitmap
{
public:
	Bitmap();
	~Bitmap();

	Bitmap& operator = ( HBITMAP hBitmap );

	BOOL operator == ( HBITMAP hBitmap );

	BOOL operator != ( HBITMAP hBitmap );

	operator HBITMAP();

	BOOL Create( int nWidth, int nHeight, UINT uPlanes, UINT uBitCount, const VOID *lpBits );

	BOOL CreateCompatible( HDC hdc, int nWidth, int nHeight );

	BOOL CreateCompatible( HWND hWnd, int nWidth, int nHeight );

	BOOL Load( LPCTSTR lpszFileName );

	BOOL Paint( HWND hWnd, int nLeft, int nTop );

private:
	BOOL UpdateSizeValues();

protected:
	HBITMAP m_hBitmap;
	int m_nWidth;
	int m_nHeight;

}; // End of class Bitmap
