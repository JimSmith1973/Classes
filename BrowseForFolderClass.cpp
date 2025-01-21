// BrowseForFolderClass.cpp

#include "BrowseForFolderClass.h"

int CALLBACK BrowseCallbackProcedure( HWND hWnd, UINT uMessage, LPARAM, LPARAM lpData )
{
	// Select message
	switch( uMessage )
	{
		case BFFM_INITIALIZED:
		{
			// An initialised message

			// Set selection
			SendMessage( hWnd, BFFM_SETSELECTION, ( WPARAM )TRUE, ( LPARAM )lpData );

			// Break out of switch
			break;

		} // End of an initialised message

	} // End of selection for message

	return 0;

} // End of function BrowseCallbackProcedure

BrowseForFolder::BrowseForFolder()
{
	// Initialise member variables
	::ZeroMemory( &m_browseInfo, sizeof( m_browseInfo ) );

} // End of function BrowseForFolder::BrowseForFolder
 
BrowseForFolder::~BrowseForFolder()
{
	// Clear member variables
	::ZeroMemory( &m_browseInfo, sizeof( m_browseInfo ) );

} // End of function BrowseForFolder::~BrowseForFolder

BOOL BrowseForFolder::Browse( LPTSTR lpszFolderPath, LPCTSTR lpszTitle )
{
	BOOL bResult = FALSE;

	// Clear browser information structure
	ZeroMemory( &m_browseInfo, sizeof( BROWSEINFO ) );

	// Initialise browser information structure
	m_browseInfo.lpfn		= BrowseCallbackProcedure;
	m_browseInfo.ulFlags	= ( BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE );
	m_browseInfo.hwndOwner	= NULL;
	m_browseInfo.lpszTitle	= lpszTitle;
	m_browseInfo.lParam		= ( LPARAM )lpszFolderPath;

	// Browse for folder
	m_lpItemIdList = SHBrowseForFolder( &m_browseInfo );

	// Ensure that a folder was selected
	if( m_lpItemIdList != NULL )
	{
		// Successfully selected folder

		// Allocate string memory
		LPTSTR lpszBuffer = new char[ STRING_LENGTH ];

		// Get path from id list
		if( SHGetPathFromIDList( m_lpItemIdList, lpszBuffer ) )
		{
			// Successfully got path from id list

			// Update folder path
			lstrcpy( lpszFolderPath, lpszBuffer );

			// Update return value_comp
			bResult = TRUE;
		} // End of successfully got path from id list

		// Free string memory
		delete [] lpszBuffer;

	} // End of successfully selected folder

	return bResult;

} // End of function BrowseForFolder::Browse

/*
BrowseForFolder::
{
} // End of function BrowseForFolder::
*/