#pragma once
#include "SecondaryServer.h"
#include <WinSock2.h>
#include <Windows.h>
#include "Message.h"
#include <iostream>
#include "Helper.h"
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <list>
#include <map>

#define SECONDARY_SERVER_CONNECTED 100
#define USER_LOGGED_IN 101
#define USER_SIGNED_UP 102

class Server
{
public:
	Server();  //Ctor
	~Server(); //Detor

	void serve(int port);

	/*
	* The function supposed to deal with the messages that are inthe queue. Now it can only handle client's login, needto fix it later.
	*/
	void messagesHandler();

private:
	std::map<std::string, SOCKET> _clients;
	std::list<SecondaryServer*> _secondaryServers;
	SOCKET _serverSocket;
	std::queue<Message> _messagesQueue;
	std::mutex _messagesMutex;
	std::condition_variable _messagesCv;
	std::mutex _secondaryServersMu;
	std::condition_variable _secondayServersCv;

	void accept();
	void clientHandler(SOCKET clientSocket);
	void addMessageToMessagesQueue(int code, std::string sender, std::string reciever, std::string content, SOCKET socket);
	void addSecondaryServer(SOCKET socket, int id);
};

