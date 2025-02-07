// ArgumentListClass.h

#pragma once

#include <windows.h>

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#define ARGUMENT_LIST_CLASS_FIRST_INPUT_PARAMETER								1

class ArgumentList
{
public:
	ArgumentList();
	~ArgumentList();

	ArgumentList& operator = ( LPWSTR *lpszArgumentList );

	operator LPWSTR();

	BOOL Get();

	BOOL GetArgument( int nWhichArgument, LPTSTR lpszArgument );

	int GetArgumentCount();

	int ProcessArguments( void( *lpArgumentFunction )( LPCTSTR lpszArgument ) );

protected:
	LPWSTR *m_lpszArgumentList;
	int m_nArgumentCount;

}; // End of class ArgumentList
