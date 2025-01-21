// BrowseForFolderClass.h

#pragma once

#include <windows.h>
#include <shlobj.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define BROWSE_FOR_FOLDER_CLASS_DEFAULT_TITLE									"Select a Folder"

class BrowseForFolder
{
public:
	BrowseForFolder();
	~BrowseForFolder();

	BOOL Browse( LPTSTR lpszFolderPath, LPCTSTR lpszTitle = BROWSE_FOR_FOLDER_CLASS_DEFAULT_TITLE );

protected:
	BROWSEINFO m_browseInfo;
	LPITEMIDLIST m_lpItemIdList;

}; // End of class BrowseForFolder
