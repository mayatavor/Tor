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
	static SOCKET createSocket(int port, std::string ip);

private:
	std::map<std::string, SOCKET> _clients;
	//std::vector<SecondaryServer*> _secondaryServers;
	std::map<int, SecondaryServer> _secondaryServers;
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

	//This function handles get chat history (get the privious messages of a specific chat) request.
	Message* caseGetChatHistory(std::vector<std::string> args);

	//This function handles the secondary server connect request.
	Message* caseSecondaryServerConnected(std::vector<std::string> args, SOCKET socket);

	void sendBroadcastMessage(Message* msg);

	void sendUsersWhenNewJoins(std::string joinedUsername);

	void sendWhenUserLoggedOut(std::string leftUsername);

	void sendUserMessage(std::string username, std::string content, std::string senderUsername, bool isGhost);

	//The function iterates through the map of the clients and creates a list with the online usernames except the given username.
	std::list<std::string> getOnlineUsernamesExceptMe(std::string myUsername);
	void accept();
	void clientHandler(SOCKET clientSocket, int port);
	Message* addMessageToMessagesQueue(std::string allMsg, SOCKET socket, int port);
	void addSecondaryServer(SOCKET socket, int id, std::pair<int, int> publicKey, int port);

	/*
	* This fucntion generates rrandom ids of servers and saves them into a vector and returns it.
	* input: The number of servers to generate.
	* output: The vercotr that contains the server's ids
	*/
	std::vector<int> getServersRoute(int numOfServers);
	std::map<int, SOCKET> checkServersValidity();
	
	//void verifyServer(int serverId, bool& answer);
};

