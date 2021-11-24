#pragma once
#include "Message.h"
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include "Helper.h"
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

#define SECONDARY_SERVER_CONNECTED 100
#define USER_LOGGED_IN 101
#define USER_SIGNED_UP 102

class Server
{
public:
	Server(int secondaryServersNum);  //Ctor
	~Server(); //Detor

	void serve(int port);
	void messagesHandler();

private:
	std::map<std::string, SOCKET> _clients;
	SOCKET*_seconaryServers;
	std::queue<Message> _messagesQueue;
	std::mutex _messagesMutex;
	std::condition_variable _messagesCv;
	std::mutex _secondaryServersMu;
	std::condition_variable _secondayServersCv;
	SOCKET _serverSocket;

	void accept();
	void clientHandler(SOCKET clientSocket);
	void addMessageToMessagesQueue(int code, std::string sender, std::string reciever, std::string content, SOCKET socket);
	void addSecondaryEerver(SOCKET socket);
};

