// TemplateClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

class Template
{
public:
	Template();
	~Template();

	Template& operator = ( HWND hWnd );

	BOOL operator == ( HWND hWnd );

	BOOL operator != ( HWND hWnd );

	operator HWND();

protected:
	HWND m_hWnd;

}; // End of class Template
