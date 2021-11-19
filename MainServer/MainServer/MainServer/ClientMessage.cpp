#include "ClientMessage.h"

ClientMessage::ClientMessage(int code, std::string sender, std::string sendTo, std::string messageConent, SOCKET& senderSocket)
{
	this->_code = code;
	this->_sender = sender;
	this->_sendTo = sendTo;
	this->_messageContent = messageConent;
	this->_senderSocket = senderSocket;
}

ClientMessage::~ClientMessage() = default;

std::string ClientMessage::getSender() const
{
	return this->_sender;
}

std::string ClientMessage::getSendTo() const
{
	return this->_sendTo;
}

std::string ClientMessage::GetMessageContent() const
{
	return this->_messageContent;
}
int ClientMessage::getCode()
{
	return this->_code;
}
SOCKET& ClientMessage::getSocket()
{
	return this->_senderSocket;
}
