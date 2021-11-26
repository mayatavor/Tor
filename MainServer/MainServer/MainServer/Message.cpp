#include "Message.h"

Message::Message(int code, std::string sender, std::string sendTo, std::string messageConent, SOCKET& senderSocket)
{
	this->_code = code;
	this->_sender = sender;
	this->_sendTo = sendTo;
	this->_messageContent = messageConent;
	this->_senderSocket = senderSocket;
}

Message::~Message() = default;

std::string Message::getSender() const
{
	return this->_sender;
}

std::string Message::getSendTo() const
{
	return this->_sendTo;
}

std::string Message::GetMessageContent() const
{
	return this->_messageContent;
}
int Message::getCode()
{
	return this->_code;
}
SOCKET& Message::getSocket()
{
	return this->_senderSocket;
}
