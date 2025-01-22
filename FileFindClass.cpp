// FileFindClass.cpp

#include "FileFindClass.h"

FileFind::FileFind()
{
	// Allocate string memory
	m_lpszParentFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Clear parent folder path
	m_lpszParentFolderPath[ 0 ] = ( char )NULL;

	// Initialise member variables
	::ZeroMemory( &m_wfd, sizeof( m_wfd ) );
	::ZeroMemory( &m_hFileFind, sizeof( m_hFileFind ) );

} // End of function FileFind::FileFind
 
FileFind::~FileFind()
{
	// Clear member variables
	::ZeroMemory( &m_wfd, sizeof( m_wfd ) );
	::ZeroMemory( &m_hFileFind, sizeof( m_hFileFind ) );

	// Free string memory
	delete [] m_lpszParentFolderPath;

} // End of function FileFind::~FileFind

BOOL FileFind::Close()
{
	// Close file find
	return ::FindClose( m_hFileFind );

} // End of function FileFind::Close

BOOL FileFind::First( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter )
{
	BOOL bResult = FALSE;

	// Allocate string memory
	LPTSTR lpszFullSearchPattern = new char[ STRING_LENGTH + sizeof( char ) ];

	// Store parent folder path
	lstrcpy( m_lpszParentFolderPath, lpszFolderPath );

	// Ensure that parent folder path ends in a back-slash character
	if( m_lpszParentFolderPath[ lstrlen( m_lpszParentFolderPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
	{
		// Parent folder path does not end in a back-slash character parent folder path

		// Append a back-slash character onto
		lstrcat( m_lpszParentFolderPath, ASCII_BACK_SLASH_STRING );

	} // End of parent folder path does not end in a back-slash character parent folder path

	// Copy parent folder path into full search pattern
	lstrcpy( lpszFullSearchPattern, m_lpszParentFolderPath );

	// Append file filter onto full search pattern
	lstrcat( lpszFullSearchPattern, lpszFileFilter );

	// Find first file
	m_hFileFind = ::FindFirstFile( lpszFullSearchPattern, &m_wfd );

	// Ensure that first file was found
	if( m_hFileFind != INVALID_HANDLE_VALUE )
	{
		// Successfully found first file

		// Update return value
		bResult = TRUE;

	} // End of successfully found first file

	return bResult;

} // End of function FileFind::First

LPTSTR FileFind::GetFileName( LPTSTR lpszFileName )
{
	// Get file name
	return lstrcpy( lpszFileName, m_wfd.cFileName );

} // End of function FileFind::GetFileName

LPTSTR FileFind::GetFilePath( LPTSTR lpszFilePath )
{
	// Copy parent folder path into file path
	lstrcpy( lpszFilePath, m_lpszParentFolderPath );

	// Append found item name onto file path
	lstrcat( lpszFilePath, m_wfd.cFileName );

	return lpszFilePath;

} // End of function FileFind::GetFilePath

BOOL FileFind::IsDots()
{
	BOOL bResult = FALSE;

	// See if item is dots
	if( m_wfd.cFileName[ 0 ] == ASCII_FULL_STOP_CHARACTER )
	{
		// Item is dots

		// Update return value
		bResult = TRUE;

	} // End of item is dots

	return bResult;

} // End of function FileFind::IsDots

BOOL FileFind::IsFile()
{
	BOOL bResult = FALSE;

	// See if item is a file
	if( !( m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
	{
		// Item is a file

		// Update return value
		bResult = TRUE;

	} // End of item is a file

	return bResult;

} // End of function FileFind::IsFile

BOOL FileFind::IsFolder()
{
	BOOL bResult = FALSE;

	// See if item is a folder
	if( m_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		// Item is a folder

		// Update return value
		bResult = TRUE;

	} // End of item is a folder

	return bResult;

} // End of function FileFind::IsFolder

BOOL FileFind::Next()
{
	// Find next file
	return ::FindNextFile( m_hFileFind, &m_wfd );

} // End of function FileFind::First

/*
FileFind::
{
} // End of function FileFind::
*/