// FileClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define FILE_CLASS_UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING				"Unable to open file %s"
#define FILE_CLASS_UNABLE_TO_GET_FILE_SIZE_ERROR_MESSAGE_FORMAT_STRING			"Unable to get size of file %s"
#define FILE_CLASS_UNABLE_TO_READ_FILE_ERROR_MESSAGE_FORMAT_STRING				"Unable to read file %s"

class File
{
public:
	File();
	~File();

	File& operator = ( HANDLE hFile );

	BOOL operator == ( HANDLE hFile );

	BOOL operator != ( HANDLE hFile );

	operator HANDLE();

	BOOL Close();

	BOOL Create( LPCSTR lpszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile );

	BOOL CreateAppend( LPCSTR lpszFileName );

	BOOL CreateRead( LPCSTR lpszFileName );

	BOOL CreateWrite( LPCSTR lpszFileName );
	
	DWORD GetSize( LPDWORD lpFileSizeHigh = NULL );

	BOOL Read( LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead = NULL, LPOVERLAPPED lpOverlapped = NULL );

	BOOL Write( LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten = NULL, LPOVERLAPPED lpOverlapped = NULL );

protected:
	HANDLE m_hFile;

}; // End of class File
