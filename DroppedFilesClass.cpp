// DroppedFilesClass.cpp

#include "DroppedFilesClass.h"

DroppedFiles::DroppedFiles()
{
	// Initialise member variables
	::ZeroMemory( &m_hDrop, sizeof( m_hDrop ) );

} // End of function DroppedFiles::DroppedFiles
 
DroppedFiles::~DroppedFiles()
{
	// Clear member variables
	::ZeroMemory( &m_hDrop, sizeof( m_hDrop ) );

} // End of function DroppedFiles::~DroppedFiles

DroppedFiles& DroppedFiles::operator = ( HDROP hDrop )
{
	// Update member variables
	m_hDrop = hDrop;

	return *this;

} // End of function DroppedFiles::operator =

BOOL DroppedFiles::operator == ( HDROP hDrop )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hDrop == m_hDrop )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function DroppedFiles::operator ==

BOOL DroppedFiles::operator != ( HDROP hDrop )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hDrop != m_hDrop )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function DroppedFiles::operator !=

DroppedFiles::operator HDROP()
{
	return m_hDrop;

} // End of function DroppedFiles::operator HDROP()

BOOL DroppedFiles::Get( WPARAM wParam )
{
	BOOL bResult = FALSE;

	// Get drop handle
	m_hDrop = ( HDROP )wParam;

	// Ensure that drop handle was got
	if( m_hDrop )
	{
		// Successfully got drop handle

		// Count dropped files
		m_uFileCount = DragQueryFile( m_hDrop, ( UINT )-1, NULL, 0 );

		// Update return value
		bResult = TRUE;

	} // End of successfully got drop handle

	return bResult;

} // End of function DroppedFiles::Get

BOOL DroppedFiles::GetFilePath( UINT uWhichFile, LPTSTR lpszFilePath )
{
	BOOL bResult = FALSE;

	// Get file path
	if( ::DragQueryFile( m_hDrop, uWhichFile, lpszFilePath, STRING_LENGTH ) )
	{
		// Successfully got file path

		// Update return value
		bResult = TRUE;

	} // End of successfully got file path

	return bResult;

} // End of function DroppedFiles::GetFilePath

int DroppedFiles::Process( void( *lpDroppedFileFunction )( LPCTSTR lpszDroppedFilePath ) )
{
	int nResult = 0;

	UINT uWhichFile;

	// Allocate string memory
	LPTSTR lpszDroppedFilePath = new char[ STRING_LENGTH ];

	// Loop through dropped files
	for( uWhichFile = 0; uWhichFile < m_uFileCount; uWhichFile ++ )
	{
		// Get file path
		if( ::DragQueryFile( m_hDrop, uWhichFile, lpszDroppedFilePath, STRING_LENGTH ) )
		{
			// Successfully got file path

			// Process dropped file
			( *lpDroppedFileFunction )( lpszDroppedFilePath );

			// Update return value
			nResult ++;

		} // End of successfully got file path

	}; // End of loop through dropped files

	// Free string memory
	delete [] lpszDroppedFilePath;

	return nResult;

} // End of function DroppedFiles::Process

/*
DroppedFiles::
{
} // End of function DroppedFiles::
*/