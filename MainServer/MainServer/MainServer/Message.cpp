#include "Message.h"


Message::Message(int code, SOCKET socket)
{
	this->m_code = code;
	this->m_senderSocket = socket;
}

 int Message::getCode() 
{
	return this->m_code();
}

 SOCKET Message::getSocket()
 {
	 return this->m_senderSocket;
 }
