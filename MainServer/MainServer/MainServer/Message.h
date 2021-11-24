#pragma once
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <string>
class Message
{
public:
	Message(int code, std::string sender, std::string sendTo, std::string messageConent, SOCKET& senderSocket);  //constructor
	~Message(); //destructor

	//retruns the sender
	std::string getSender() const;

	//returns the name of the user to send to
	std::string getSendTo() const;

	//returns the message content
	std::string GetMessageContent() const;

	//returns the code of the message
	int getCode();

	//returns the socket connection between the senderand the client
	SOCKET& getSocket();

private:
	int _code;
	std::string _sender;
	std::string _sendTo;
	std::string _messageContent;
	SOCKET _senderSocket;
};

