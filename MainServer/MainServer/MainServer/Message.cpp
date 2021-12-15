#include "Message.h"
#include <iostream>
#include <sstream>

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
	this->_mt = (MessageType)std::stoi(token.substr(0, token.length() ));
	while ((pos = allMsg.find(DELIMITER)) != std::string::npos)
	{
		token = allMsg.substr(0, pos);
		std::cout << token << std::endl;
		allMsg.erase(0, pos + 1);
		this->_args.push_back(token);
	}
	this->_args.push_back(allMsg);
}

Message::Message(MessageType type, std::vector<std::string> args)
{
	this->_mt = type;
	this->_args = args;
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
	case signUp:
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

std::string Message::buildMessage()
{
	std::string msg = std::accumulate(std::begin(this->_args), std::end(this->_args), std::string(),
		[](std::string& ss, std::string& s) {
			return ss.empty() ? s : ss + DELIMITER + s;
		});

	std::string msgcontent = std::to_string(this->_mt) + DELIMITER + msg;
	std::string len =  std::to_string(msgcontent.length() + 1);
	len.insert(len.begin(), 5 - len.length(), '0');
	/*len += DELIMITER;
	len += msgcontent;*/
	std::stringstream ss;
	ss << len << msgcontent;
	return  ss.str();
}
