// DroppedFilesClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class DroppedFiles
{
public:
	DroppedFiles();
	~DroppedFiles();

	DroppedFiles& operator = ( HDROP hDrop );

	BOOL operator == ( HDROP hDrop );

	BOOL operator != ( HDROP hDrop );

	operator HDROP();

	BOOL Get( WPARAM wParam );

	BOOL GetFilePath( UINT uWhichFile, LPTSTR lpszFilePath );

	int Process( void( *lpDroppedFileFunction )( LPCTSTR lpszDroppedFilePath ) );

protected:
	HDROP m_hDrop;
	UINT m_uFileCount;

}; // End of class DroppedFiles
