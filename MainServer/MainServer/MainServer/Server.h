#pragma once
#pragma comment(lib, "Ws2_32.lib")
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
#include "DatabaseAccess.h"
#include "User.h"


#define DELIMITER "~"

class Server
{
public:
	Server();  //Ctor
	~Server(); //Detor

	void serve(int port);

	void messagesHandler();

private:
	std::map<std::string, SOCKET> _clients;
	std::list<SecondaryServer*> _secondaryServers;
	SOCKET _serverSocket;
	std::queue<std::pair<SOCKET, Message>> _messagesQueue;
	std::mutex _messagesMutex;
	std::condition_variable _messagesCv;
	std::mutex _secondaryServersMu;
	std::condition_variable _secondayServersCv;
	DatabaseAccess* _db;

	Message* caseLogin(std::vector<std::string> args);
	Message* caseSignUp(std::vector<std::string> args);
	Message* caseLogout(std::vector<std::string> args);
	Message* caseAddFavorites(std::vector<std::string> args);
	//Message* getFavorites(std::vector<std::string> args);
	Message* caseGetUsers(std::vector<std::string> args);
	Message* caseSendMessage(std::vector<std::string> arg);
	Message* caseGetChatHistory(std::vector<std::string> args);

	void accept();
	void clientHandler(SOCKET clientSocket, int port);
	void addMessageToMessagesQueue(std::string allMsg, SOCKET socket, int port);
	void addSecondaryServer(SOCKET socket, int id);

};

