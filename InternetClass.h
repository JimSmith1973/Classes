// InternetClass.h
//
// Note that the following text must be added to the end of the g++ command
//  -lwininet

#pragma once

#include <windows.h>
#include <wininet.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define INTERNET_CLASS_USER_AGENT												"InetURL/1.0"

#define INTERNET_CLASS_DOWNLOAD_BUFFER_LENGTH									1024

#define INTERNET_CLASS_DOWNLOADING_STATUS_MESSAGE_FORMAT_STRING					"Downloading %s ..."
#define INTERNET_CLASS_SUCCESSFULLY_DOWNLOADED_STATUS_MESSAGE_FORMAT_STRING		"Successfully downloaded %s to %s"
#define INTERNET_CLASS_UNABLE_TO_DOWNLOAD_STATUS_MESSAGE_FORMAT_STRING			"Unable to download %s"

#define INTERNET_CLASS_UNABLE_TO_CONNECT_TO_INTERNET_ERROR_MESSAGE				"Unable to connect to internet"

class Internet
{
public:
	Internet();
	~Internet();

	Internet& operator = ( HINTERNET hInternet );

	BOOL operator == ( HINTERNET hInternet );

	BOOL operator != ( HINTERNET hInternet );

	operator HINTERNET();

	BOOL Close();

	BOOL Connect( LPCSTR lpszAgent = INTERNET_CLASS_USER_AGENT, DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG, LPCSTR lpszProxy = NULL, LPCSTR lpszProxyBypass = NULL, DWORD dwFlags = 0 );

	BOOL DownloadFile( LPCTSTR lpszUrl, LPTSTR lpszLocalFilePath );

protected:
	HINTERNET m_hInternet;

}; // End of class Internet
