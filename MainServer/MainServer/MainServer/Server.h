#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

class Server
{
public:
	Server();  //Ctor
	~Server(); //Detor

	void serve(int port);
	void messagesHandler();

private:
	std::map<std::string, SOCKET> _clients;
	std::queue<std::string> _messagesQueue;
	std::mutex _mu;
	std::condition_variable _cv;
	SOCKET _serverSocket;

	void accept();
	void clientHandler(SOCKET clientSocket);
	void addMessageToQueue(int code, std::string sender, std::string reciever, std::string content, SOCKET clientSocket);
};

