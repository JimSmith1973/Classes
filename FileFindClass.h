// FileFindClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define FILE_FIND_CLASS_FOUND_FILES_STATUS_MESSAGE_FORMAT_STRING				"%s (%d items)"

class FileFind
{
public:
	FileFind();
	~FileFind();

	BOOL Close();

	BOOL First( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter = ALL_FILES_FILTER );

	LPTSTR GetFileName( LPTSTR lpszFileName );

	LPTSTR GetFilePath( LPTSTR lpszFilePath );

	BOOL IsDots();

	BOOL IsFile();

	BOOL IsFolder();

	BOOL Next();

protected:
	WIN32_FIND_DATA m_wfd;
	HANDLE m_hFileFind;
	LPTSTR m_lpszParentFolderPath;

}; // End of class FileFindClass
