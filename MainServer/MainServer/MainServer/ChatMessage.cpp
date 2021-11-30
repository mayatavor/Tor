#include "ChatMessage.h"

ChatMessage::ChatMessage(int code, std::string sender, std::string sendTo, std::string messageConent, SOCKET& senderSocket) : Message(code, socket)
{
	this->_sender = sender;
	this->_sendTo = sendTo;
	this->_messageContent = messageConent;
}


std::string ChatMessage::getSender() const
{
	return this->_sender;
}

std::string ChatMessage::getSendTo() const
{
	return this->_sendTo;
}

std::string ChatMessage::GetMessageContent() const
{
	return this->_messageContent;
}

int ChatMessage::getCode()
{
	return this->_code;
}
