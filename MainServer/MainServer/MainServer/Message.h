#pragma once
#include "MessageType.h"
#include <vector>
#include <string>
#include <numeric>
#define DELIMITER "≡"
//#include <WinSock2.h>
//#include <Windows.h>
//
//class Message
//{
//public:
//	Message(int code, SOCKET socket);
//	~Message() = default;
//
//	
//	int getCode();
//	SOCKET getSocket();
//
//
//protected:
//	int m_code;
//	SOCKET m_senderSocket;
//};
//


class Message
{
public:
	Message(std::string allMsg);
	Message(MessageType type, std::vector<std::string> args);
	~Message() = default;

	std::vector<std::string> getArgs() const;
	MessageType getMessageType() const;
	bool validateArgumentLength();
	std::string buildMessage();

private:
	MessageType _mt;
	std::vector<std::string> _args;

};
