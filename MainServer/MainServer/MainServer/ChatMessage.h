#pragma once
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include "Message.h"
#include <string>
class ChatMessage : public Message
{
public:
	ChatMessage(int code, std::string sender, std::string sendTo, std::string messageConent, SOCKET& senderSocket);  //constructor
//	~MessageOne(); //destructor

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

