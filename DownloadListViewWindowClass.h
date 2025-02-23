// DownloadListViewWindowClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "ListViewWindowClass.h"

#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_NAME									WC_LISTVIEW
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT							NULL
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU							NULL
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE					LVS_EX_FULLROWSELECT
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE							( WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT )
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT							CW_USEDEFAULT
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP								CW_USEDEFAULT
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH							CW_USEDEFAULT
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT							CW_USEDEFAULT
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM						NULL
#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_COLUMN_WIDTH					100

#define DOWNLOAD_LIST_VIEW_WINDOW_CLASS_CLASS_COLUMN_TITLES						{ "URL", "Local File" }

typedef enum
{
	DOWNLOAD_LIST_VIEW_WINDOW_CLASS_URL_COLUMN_ID = 0,
	DOWNLOAD_LIST_VIEW_WINDOW_CLASS_LOCAL_FILE_COLUMN_ID,

	DOWNLOAD_LIST_VIEW_WINDOW_CLASS_NUMBER_OF_COLUMNS

} DOWNLOAD_LIST_VIEW_WINDOW_CLASS_COLUMNS;

class DownloadListViewWindow : public ListViewWindow
{
public:
	DownloadListViewWindow();
	~DownloadListViewWindow();

	DownloadListViewWindow& operator = ( HWND hWnd );

	BOOL operator == ( HWND hWnd );

	BOOL operator != ( HWND hWnd );

	operator HWND();

	BOOL Create( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszWindowText = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_TEXT, HMENU hMenu = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_MENU, DWORD dwExStyle = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE, DWORD dwStyle = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_STYLE, int nLeft = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_LEFT, int nTop = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_TOP, int nWidth = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_WIDTH, int nHeight = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_HEIGHT, LPVOID lpParam = DOWNLOAD_LIST_VIEW_WINDOW_CLASS_DEFAULT_LP_PARAM );

protected:

}; // End of class DownloadListViewWindow
