#pragma once
#include <WinSock2.h>
#include <Windows.h>

class Message
{
public:
	Message(int code, SOCKET socket);
	~Message() = default;

	
	int getCode();
	SOCKET getSocket();


protected:
	int m_code;
	SOCKET m_senderSocket;
};

