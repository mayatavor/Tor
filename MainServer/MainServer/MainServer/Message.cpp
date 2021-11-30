#include "Message.h"
#include <iostream>
#define DELIMITER "≡"

//
//Message::Message(int code, SOCKET socket)
//{
//	this->m_code = code;
//	this->m_senderSocket = socket;
//}
//
// int Message::getCode() 
//{
//	return this->m_code();
//}
//
// SOCKET Message::getSocket()
// {
//	 return this->m_senderSocket;
// }
//
// Message::Message(std::string allMsg)
// {
// }


Message::Message(std::string allMsg) 
{
	int pos = allMsg.find(DELIMITER);
	std::string token = allMsg.substr(0, pos);
	std::cout << token << std::endl;
	allMsg.erase(0, pos + 1);
	this->_mt = (MessageType)std::stoi(token.substr(0, token.length() - 1));
	while ((pos = allMsg.find(DELIMITER)) != std::string::npos)
	{
		token = allMsg.substr(0, pos);
		std::cout << token << std::endl;
		allMsg.erase(0, pos + 1);
		this->_args.push_back(token);
	}
}

std::vector<std::string> Message::getArgs() const
{
	return this->_args;
}

MessageType Message::getMessageType() const
{
	return this->_mt;
}

bool Message::validateArgumentLength()
{
	switch (this->_mt)
	{
	case logIn:
		if (this->_args.size() != 4)
			return false;
		break;
	case signIn:
		if (this->_args.size() != 4)
			return false;
		break;
	case ghostLogIn:
		return true;
		break;
	case sendChatMessage:
		if (this->_args.size() != 3)
			return false;
	default:
		break;
	}
	return true;
}
