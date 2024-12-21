// MessageClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Message
{
public:
	Message();
	~Message();

	Message& operator = ( MSG hMsg );

	operator int();

	operator MSG();

	BOOL Dispatch();

	BOOL Get( HWND hWnd = NULL, UINT wMsgFilterMin = 0, UINT wMsgFilterMax = 0 );

	BOOL Translate();

protected:
	MSG m_hMsg;

}; // End of class Message
