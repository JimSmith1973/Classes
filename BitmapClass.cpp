// BitmapClass.cpp

#include "BitmapClass.h"

Bitmap::Bitmap()
{
	// Clear bitmap structure
	::ZeroMemory( &m_hBitmap, sizeof( m_hBitmap ) );

	// Initialise member variables
	m_nWidth	= 0;
	m_nHeight	= 0;

} // End of function Bitmap::Bitmap
 
Bitmap::~Bitmap()
{
	// Clear bitmap structure
	::ZeroMemory( &m_hBitmap, sizeof( m_hBitmap ) );

} // End of function Bitmap::~Bitmap

Bitmap& Bitmap::operator = ( HBITMAP hBitmap )
{
	// Update bitmap structure
	m_hBitmap = hBitmap;

	// Update size values
	UpdateSizeValues();

	return *this;

} // End of function Bitmap::operator =

BOOL Bitmap::operator == ( HBITMAP hBitmap )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hBitmap == m_hBitmap )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Bitmap::operator ==

BOOL Bitmap::operator != ( HBITMAP hBitmap )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hBitmap != m_hBitmap )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Bitmap::operator !=

Bitmap::operator HBITMAP()
{
	return m_hBitmap;

} // End of function Bitmap::operator HBITMAP()

BOOL Bitmap::Create( int nWidth, int nHeight, UINT uPlanes, UINT uBitCount, const VOID *lpBits )
{
	BOOL bResult = FALSE;

	// Create bitmap
	m_hBitmap = ::CreateBitmap( nWidth, nHeight, uPlanes, uBitCount, lpBits );

	// Ensure that bitmap was created
	if( m_hBitmap )
	{
		// Successfully created bitmap

		// Update member variables
		m_nWidth	= nWidth;
		m_nHeight	= nHeight;

		// Update return value
		bResult = TRUE;

	} // End of successfully created bitmap

	return bResult;

} // End of function Bitmap::Create

BOOL Bitmap::CreateCompatible( HDC hdc, int nWidth, int nHeight )
{
	BOOL bResult = FALSE;

	// Create compatible bitmap
	m_hBitmap = ::CreateCompatibleBitmap( hdc, nWidth, nHeight );

	// Ensure that compatible bitmap was created
	if( m_hBitmap )
	{
		// Successfully created compatible bitmap

		// Update member variables
		m_nWidth	= nWidth;
		m_nHeight	= nHeight;

		// Update return value
		bResult = TRUE;

	} // End of successfully created compatible bitmap

	return bResult;

} // End of function Bitmap::CreateCompatible

BOOL Bitmap::CreateCompatible( HWND hWnd, int nWidth, int nHeight )
{
	// Create compatible bitmap
	return CreateCompatible( ::GetDC( hWnd ), nWidth, nHeight );

} // End of function Bitmap::CreateCompatible

BOOL Bitmap::Load( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Open file
	hFile = ::CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = ::GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size
			HGLOBAL hGlobal;

			// Allocate global memory
			hGlobal = ::GlobalAlloc( GPTR, dwFileSize );
			
			// Ensure that global memory was allocated
			if( hGlobal )
			{
				// Successfully allocated global memory
				LPVOID lpGlobal;

				// Get pointer to global memory
				lpGlobal = ( LPVOID )hGlobal;

				// Read data from file
				if( ::ReadFile( hFile, lpGlobal, dwFileSize, NULL, NULL ) )
				{
					// Successfully read data from file
					IStream *lpStream;

					// Create stream
					::CreateStreamOnHGlobal( hGlobal,false,&lpStream );

					// Ensure that stream was created
					if( lpStream )
					{
						// Successfully created stream
						IPicture *lpPicture;

						// Load picture
						::OleLoadPicture( lpStream, 0, false, IID_IPicture, ( LPVOID * )&lpPicture );

						// Ensure that picture was loaded
						if( lpPicture )
						{
							// Successfully loaded picture
							HBITMAP hBitmapTemporary = NULL;

							// Copy picture into temporary bitmap handle
							lpPicture->get_Handle( ( unsigned int * )&hBitmapTemporary );

							// Copy from tempory bitmap handle into member bitmap
							m_hBitmap = ( HBITMAP )CopyImage( hBitmapTemporary, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG );

							// Note that the temporary bitmap will be destroyed as soon as the picture is released, so
							// we can't just copy straight into the member bitmap

							// Update size values
							UpdateSizeValues();

							// Release picture
							lpPicture->Release();

							// Update return value
							bResult = TRUE;

						} // End of successfully loaded picture

					// Release stream
						lpStream->Release();

					} // End of successfully created stream

				} // End of successfully read data from file

				// Free global memory
				GlobalFree( hGlobal );

			} // End of successfully allocated global memory

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function Bitmap::Load

BOOL Bitmap::Paint( HWND hWnd, int nLeft, int nTop )
{
	BOOL bResult = FALSE;

	PAINTSTRUCT ps;
	HDC hdcWindow;
	HDC hdcBitmap;
	HBITMAP hbmOld;

	// Begin painting
	hdcWindow = BeginPaint( hWnd, &ps );

	// Create bitmap dc
	hdcBitmap = CreateCompatibleDC( hdcWindow );

	// Copy bitmap into dc
	hbmOld = ( HBITMAP )SelectObject( hdcBitmap, m_hBitmap );

	// Paint bitmap onto window
	BitBlt( hdcWindow, nLeft, nTop, m_nWidth, m_nHeight, hdcBitmap, 0, 0, SRCCOPY );

	// Remove bitmap from dc
	SelectObject( hdcBitmap, hbmOld );

	// Delete bitmap dc
	DeleteDC( hdcBitmap );

	// End painting
	EndPaint( hWnd, &ps );

	return bResult;

} // End of function Bitmap::Paint

BOOL Bitmap::UpdateSizeValues()
{
	BOOL bResult = FALSE;

	BITMAP bitmap;

	// Copy bitmap handle into bitmap structure
	if( GetObject( m_hBitmap, sizeof( bitmap ), &bitmap ) )
	{
		// Successfully copied bitmap handle into bitmap structure

		// Update member variables
		m_nWidth	= bitmap.bmWidth;
		m_nHeight	= bitmap.bmHeight;

		// Update return value
		bResult = TRUE;

	} // End of successfully copied bitmap handle into bitmap structure

	return bResult;

} // End of function Bitmap::UpdateSizeValues

/*
Bitmap::
{
} // End of function Bitmap::
*/