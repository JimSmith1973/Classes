// MessageClass.cpp

#include "MessageClass.h"

Message::Message()
{
	// Initialise member variables
	ZeroMemory( &m_hMsg, sizeof( m_hMsg ) );

} // End of function Message::Message
 
Message::~Message()
{
	// Clear member variables
	ZeroMemory( &m_hMsg, sizeof( m_hMsg ) );

} // End of function Message::~Message

Message& Message::operator = ( MSG hMsg )
{
	// Update member variables
	m_hMsg = hMsg;

	return *this;

} // End of function Message::operator =

Message::operator int()
{
	return m_hMsg.wParam;

} // End of function Message::operator int()

Message::operator MSG()
{
	return m_hMsg;

} // End of function Message::operator MSG()

BOOL Message::Dispatch()
{
	// Dispatch message
	return DispatchMessage( &m_hMsg );

} // End of function Message::Dispatch

BOOL Message::Get( HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax )
{
	// Get message
	return GetMessage( &m_hMsg, hWnd, wMsgFilterMin, wMsgFilterMax );

} // End of function Message::Get

BOOL Message::Translate()
{
	// Translate message
	return TranslateMessage( &m_hMsg );

} // End of function Message::Translate

/*
Message::
{
} // End of function Message::
*/