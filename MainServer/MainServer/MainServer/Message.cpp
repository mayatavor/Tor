#include "Message.h"
#include <iostream>
#include <sstream>

#define DECRYPT_KEY -13;
#define ENCRYPT_KEY 13


Message::Message(std::string allMsg) 
{
	//allMsg = this->encryptAndDecrypt(-13, allMsg);
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
	/*if (this->_mt == MessageType::logIn || this->_mt == MessageType::signUp)
		this->_args.push_back(std::to_string(port));*/
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
	case MessageType::logIn:
		if (this->_args.size() != 4)
			return false;
		break;
	case MessageType::signUp:
		if (this->_args.size() != 4)
			return false;
		break;
	case MessageType::ghostLogIn:
		if (this->_args.size() != 2)
			return false;
		break;
	case MessageType::sendChatMessage:
		if (this->_args.size() != 3)
			return false;
		break;
	case MessageType::logout:
		if (this->_args.size() != 1)
			return false;
		break;
	case MessageType::favoriteUser:
		if (this->_args.size() != 2)
			return false;
		break;
	case MessageType::getUsers:
		if (this->_args.size() != 1)
			return false;
		break;
	case MessageType::getChatHistory:
		if (this->_args.size() != 2)
			return false;
		break;
	default:
		break;
	}
	return true;
}

std::string Message::buildMessage(int key)
{
	std::string msg = std::accumulate(std::begin(this->_args), std::end(this->_args), std::string(),
		[](std::string& ss, std::string& s) {
			return ss.empty() ? s : ss + DELIMITER + s;
		});

	std::string msgcontent = std::to_string(this->_mt) + DELIMITER + msg;
	/*if(key != 0)
		msgcontent = this->encryptAndDecrypt(key, msgcontent);*/
	std::string len =  std::to_string(msgcontent.length() + 1);
	len.insert(len.begin(), 5 - len.length(), '0');
	/*len += DELIMITER;
	len += msgcontent;*/
	std::stringstream ss;
	ss << len << msgcontent;
	return  ss.str();
}

std::string Message::encryptAndDecrypt(int key, std::string msg)
{
	std::string result = "";

	// traverse text
	for (int i = 0; i < msg.length(); i++)
	{
		// apply transformation to each character
		// Encrypt Uppercase letters
		if (isupper(msg[i]))
			result += char(int(msg[i] + key - 65) % 26 + 65);

		// Encrypt Lowercase letters
		else if (islower(msg[i]))
			result += char(int(msg[i] + key - 97) % 26 + 97);
		else
			result += msg[i];
	}

	// Return the resulting string
	return result;
}
