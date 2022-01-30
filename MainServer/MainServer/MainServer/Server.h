#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include "SecondaryServer.h"
#include "DatabaseAccess.h"
#include <WinSock2.h>
#include <Windows.h>
#include "Message.h"
#include <string>
#include <mutex>
#include <queue>
#include <list>
#include <map>


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

	//This function handles login request.
	Message* caseLogin(std::vector<std::string> args, SOCKET usersSocket);

	//This fucntion handles signup request.
	Message* caseSignUp(std::vector<std::string> args, SOCKET usersSocket);

	//This function handles login request when the client chose to login as a ghost.
	Message* caseGhostLogin(std::vector<std::string> args, SOCKET usersSocket);

	//This funcion handles logout request.
	Message* caseLogout(std::vector<std::string> args);

	//This function handles add favorite request.
	Message* caseAddFavorites(std::vector<std::string> args);
	
	//This function handles get users request.
	Message* caseGetUsers(std::vector<std::string> args);

	//This function handles send message request.
	Message* caseSendMessage(std::vector<std::string> args);

	//This message handles get chat history (get the privious messages of a specific chat) request.
	Message* caseGetChatHistory(std::vector<std::string> args);

	void sendBroadcastMessage(Message* msg);

	void sendUsersWhenNewJoins(std::string joinedUsername);

	SOCKET createSocket(int port, std::string ip);

	//The function iterates through the map of the clients and creates a list with the online usernames except the given username.
	std::list<std::string> getOnlineUsernamesExceptMe(std::string myUsername);
	void accept();
	void clientHandler(SOCKET clientSocket, int port);
	void addMessageToMessagesQueue(std::string allMsg, SOCKET socket, int port);
	void addSecondaryServer(SOCKET socket, int id);

};

