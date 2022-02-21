#pragma warning(disable : 4996)
#include "Server.h"
#include "MessageType.h"
#include "serialize.h"
#include <WS2tcpip.h>
#include "Structs.h"
#include <iostream>
#include <stdlib.h>
#include "Helper.h"
#include <stdio.h>
#include <time.h>
#include <thread>
#include "User.h"
#include <sstream>
#define _WINSOCK_DEPCRECATED 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define USER_EXISTS(id, content, existsOrNot) \
 if (this->_db->doesUserExist(id) == existsOrNot)\
{ \
	std::vector<std::string> msg = { content }; \
	return new Message(error, msg); \
}

#define IN_USER_DELIMITER "::::"


Server::Server()
{
	this->_db = new DatabaseAccess();
	this->_db->open();
	
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	delete this->_db;
	this->_secondaryServers.clear();
	//delete &this->_secondaryServers;
	try
	{
		//Nedd to be added: free the queues memory


		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	std::thread t(&Server::messagesHandler, this);

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		accept();
	}
}

Message* Server::caseLogin(std::vector<std::string> args, SOCKET usersSocket)
{
	User u = this->_db->getUser(args[0]);
	if (u.getId() == -1)
	{
		std::vector<std::string> args = { "User doesn't exist" };
		Message* msg = new Message(error, args);
		return msg;
	}
	else if (args[1] != u.getPassword())
	{
		std::vector<std::string> args = { "Wrong Password" };
		Message* msg = new Message(error, args);
		return msg;
	}
 	this->sendUsersWhenNewJoins(args[0]);
	this->_clients.insert(std::pair<std::string, SOCKET>(args[0], usersSocket));
	this->_db->updateUsersIpAndPort(args[0], args[3], args[2]);
	return new Message(success, { "LoggedIn successfully" });
}

Message* Server::caseSignUp(std::vector<std::string> args, SOCKET usersSocket)
{
	if (this->_db->doesUserExist(args[0]))
	{
		std::vector<std::string> msg = { "User with this usename already exists" };
		return new Message(error, msg);
	}
	//USER_EXISTS(args[0], "User with this usename already exists", true);
	std::cout << "port " << args[2] << std::endl;
	if (this->_db->createUser(args[0], args[1], args[3], args[2])) {
		std::vector<std::string> answerArgs = { "SignedUp Successfully" };
		this->sendUsersWhenNewJoins(args[0]);
		this->_clients.insert(std::pair<std::string, SOCKET>(args[0], usersSocket));   //Add the user's socket to the online cients map.
		return new Message(MessageType::success, answerArgs);
	}
	else {
		std::vector<std::string> answerArgs = { "Error accurd while signing up" };
		return new Message(MessageType::error, answerArgs);
	}
}

Message* Server::caseGhostLogin(std::vector<std::string> args, SOCKET usersSocket)
{
	srand(time(NULL));
	int ghostIdentifier = rand() % 5000;
	std::string username = "ghost" + std::to_string(ghostIdentifier);
	std::vector<std::string> answerArgs;
	if (this->_db->createUser(username, "", args[1], args[0]))
	{
		//this->sendUsersWhenNewJoins(username);
		this->_clients.insert(std::pair<std::string, SOCKET>(username, usersSocket));
		answerArgs.push_back(username);
		return new Message(MessageType::success, answerArgs);

	}
	else {
		answerArgs.push_back("Error while logging ghost in");
		return new Message(MessageType::error, answerArgs);
	}
}

Message* Server::caseLogout(std::vector<std::string> args)
{
	/*if (!this->_db->doesUserExist(args[0])) {
		std::vector<std::string> msg = { "User doesn't exist" };
		return new Message(error, msg);
	}*/
	//USER_EXISTS(args[0], "User doesn't exist", false);
	std::map<std::string, SOCKET>::iterator it = this->_clients.find(args[0]);
	if (it == this->_clients.end()) {
		std::vector<std::string> msg = { "User doesn't connected so he can't be logged out" };
		return new Message(error, msg);
	}
	this->_clients.erase(it);
	this->_db->deleteUser(args[0]);
	this->sendWhenUserLoggedOut(args[0]);
	std::vector<std::string> msg = { "User logged out successfuly" };
	return new Message(success, msg);
}

Message* Server::caseAddFavorites(std::vector<std::string> args)
{
	USER_EXISTS(args[0], "User doesn't exist", false);
	bool succedded = this->_db->addFavorite(args[0], args[1]);
	if (succedded)
	{
		std::vector<std::string> answerArgs = { "Added successfully" };
		return new Message(success, answerArgs);
	}
	std::vector<std::string> answerArgs = { "User can't be added to favorites." };
	return new Message(MessageType::error, answerArgs);
}


void Server::messagesHandler()
{
	Helper h;
	while (true)
	{
		std::unique_lock<std::mutex> lock(this->_messagesMutex);
		this->_messagesCv.wait(lock, [this] {return !this->_messagesQueue.empty(); });
		std::pair<SOCKET, Message> m = this->_messagesQueue.front();
		this->_messagesQueue.pop();
		Message* msg = nullptr;
		lock.unlock();
		if (!m.second.validateArgumentLength())
			std::cout << "Invalid Message" << std::endl;
		else
		{
			std::vector<std::string> args = m.second.getArgs();
			switch (m.second.getMessageType())
			{
			case MessageType::logIn:
				msg = caseLogin(args, m.first);
				break;
			case MessageType::signUp:
				msg = caseSignUp(args, m.first);
				break;
			case MessageType::ghostLogIn:
				msg = caseGhostLogin(args, m.first);
				break;
			case MessageType::logout:
				msg = caseLogout(args);
				break;
			case MessageType::favoriteUser:
				msg = caseAddFavorites(args);
				break;
			case MessageType::getUsers:
				msg = caseGetUsers(args);
				break;
			case MessageType::sendChatMessage:
				msg = caseSendMessage(args);
				break;
			case MessageType::getChatHistory:
				msg = caseGetChatHistory(args);
				break;
			default:
				break;
			}
			if(msg)
				h.sendData(m.first, msg->buildMessage());
		}
		if(msg)
			delete msg;
	}
}


Message* Server::caseGetUsers(std::vector<std::string> args)
{
	///std::list<std::string> allUsers = this->_db->getUsers();
	std::list<std::string> allUsers = this->getOnlineUsernamesExceptMe(args[0]);
	std::list<std::string> favorites = this->_db->getFavoritesOfUser(args[0]);
	std::vector<std::string> msg = serialize::serializeUsers(allUsers, favorites);
	return new Message(MessageType::getUsers, msg);
}

Message* Server::caseSendMessage(std::vector<std::string> args)
{
	User u1 = this->_db->getUser(args[0]);
	User u2 = this->_db->getUser(args[1]);
	std::vector<std::string> msg;
	bool success = true;
	if (u1.getId() == -1 || u2.getId() == -1)
	{
		msg.push_back("One of the users doesn't exist");
		return new Message(MessageType::error, msg);
	}
	if (true)//u1.getUsername().find("ghost") == std::string::npos && u2.getUsername().find("ghost") == std::string::npos) 
	{    //Check if the both of the users are not ghosts becuse there is bo need to save chat history when ghosts.
		Chat chat = this->_db->getChatByUsers(args[0], args[1]);
		if (chat.getChatId() == -1)
			this->_db->createChat(u1.getId(), u2.getId());
		chat = this->_db->getChatByUsers(args[0], args[1]);
		success = this->_db->addMessage(args[2], chat.getChatId(), u1.getId());
	}
	if (success)
	{
		this->sendUserMessage(args[1], args[2], args[0], u1.getUsername().find("ghost") != std::string::npos);
		return nullptr;
	}
	else
	{
		msg.push_back("Couldn't send mesage:(");
		return new Message(MessageType::success, msg);
	}
}

Message* Server::caseGetChatHistory(std::vector<std::string> args)
{
	Chat chat = this->_db->getChatByUsers(args[0], args[1]);
	if (chat.getChatId() == -1) {
		std::vector<std::string> msg = { "::::none::::" };
		return new Message(MessageType::success, msg);
	}
	std::list<MessagesListItem> messages = this->_db->getChatHistory(chat.getChatId());
	std::vector<std::string> msg = serialize::serializeChatHistory(messages);
	return new Message(MessageType::success, msg);
}

void Server::sendBroadcastMessage(Message* msg)
{
	std::string messageString = msg->buildMessage();
	for (auto it = this->_clients.begin(); it != this->_clients.end(); it++) {
		Helper::sendData(it->second, messageString);
	}
	delete msg;
}

void Server::sendUsersWhenNewJoins(std::string joinedUsername)
{
	for (auto it = this->_clients.begin(); it != this->_clients.end(); it++) 
	{
		User u = this->_db->getUser(it->first);
		UsersListItem uli;
		uli.isFavorite = this->_db->isFavorite(it->first, joinedUsername);
		uli.usernameOther = joinedUsername;
		uli.isGhost = joinedUsername.find("ghost") != std::string::npos;
		std::string msg = std::to_string(MessageType::getUsersWhenJoined) + DELIMITER + uli.usernameOther + IN_USER_DELIMITER + std::to_string(uli.isFavorite) + IN_USER_DELIMITER + std::to_string(uli.isGhost);
		Message* builtMessage = new Message(msg);

		SOCKET clientSocket = createSocket(u.getPort(), u.getIp());
		std::string m = builtMessage->buildMessage();
		try
		{
			Helper::sendData(clientSocket, m);
			delete builtMessage;
		}
		catch (const std::exception& e)
		{
			builtMessage = new Message(e.what());
			Helper::sendData(clientSocket, builtMessage->buildMessage());
			delete builtMessage;
		}
	}
}

void Server::sendWhenUserLoggedOut(std::string leftUsername)
{
	for (auto it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		User u = this->_db->getUser(it->first);
		UsersListItem uli;
		uli.isFavorite = this->_db->isFavorite(it->first, leftUsername);
		uli.usernameOther = leftUsername;
		uli.isGhost = leftUsername.find("ghost") != std::string::npos;
		std::string msg = std::to_string(MessageType::sendUserLeft) + DELIMITER + uli.usernameOther;
		Message* builtMessage = new Message(msg);

		SOCKET clientSocket = createSocket(u.getPort(), u.getIp());
		std::string m = builtMessage->buildMessage();
		try
		{
			Helper::sendData(clientSocket, m);
			delete builtMessage;
		}
		catch (const std::exception& e)
		{
			builtMessage = new Message(e.what());
			Helper::sendData(clientSocket, builtMessage->buildMessage());
			delete builtMessage;
		}
	}
}

void Server::sendUserMessage(std::string username, std::string content, std::string senderUsername, bool isGhost)
{
	User u = this->_db->getUser(username);
	SOCKET sock = createSocket(u.getPort(), u.getIp());
	std::string msg = "";
	if (isGhost)
		msg = std::to_string(MessageType::sendMessageFromGhost) + DELIMITER + senderUsername + DELIMITER + content;
	else
		msg = std::to_string(MessageType::sendMessageToOtherUser) + DELIMITER + senderUsername + DELIMITER + content;
	Message* builtMessage = new Message(msg);
	try
	{
		Helper::sendData(sock, builtMessage->buildMessage());
		delete builtMessage;
	}
	catch (const std::exception& e)
	{
		builtMessage = new Message(e.what());
		Helper::sendData(sock, builtMessage->buildMessage());
		delete builtMessage;
	}
}


SOCKET Server::createSocket(int port, std::string ip)
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		std::cout << "Winsock Connection Failed!" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	sockaddr_storage storage;
	int addrLen = sizeof(addr);
	IN_ADDR ipvalue;
	memset(&storage, 0, sizeof storage);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	SOCKET connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
		std::cout << "Connected!" << std::endl;
		return connection;
	}
	else 
		std::cout << "Error Connecting to Host" << std::endl;
	return NULL;
}

std::list<std::string> Server::getOnlineUsernamesExceptMe(std::string myUsername)
{
	std::map<std::string, SOCKET>::iterator it;
	std::list<std::string> usernames;
	for (it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if(it->first != myUsername && it->first.find("ghost") == std::string::npos)
			usernames.push_back(it->first);
	}
	return usernames;
}

void Server::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	
	
	// Construct sockaddr struct from the current SOCKET
	struct sockaddr_in localAddress;
	int addrSize = sizeof(localAddress);

	// Get the sockaddr information from the peer (not the sock)
	getpeername(client_socket, (struct sockaddr*)&localAddress, &addrSize);
	std::cout << "Client's port " << ntohs(localAddress.sin_port) << std::endl;

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	std::thread t(&Server::clientHandler, this, client_socket, localAddress.sin_port);
	t.detach();
}

void Server::clientHandler(SOCKET socket, int port)
{

	Helper h;
	std::string username = "";
	try
	{
		while (true)
		{
			int len = h.getIntPartFromSocket(socket, 5);
			std::string message = h.getStringPartFromSocket(socket, len);
			Message* msg = addMessageToMessagesQueue(message, socket, port);
			username = msg->getArgs()[0];
			delete msg;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what()  << " client handler" << std::endl;
		if(username.find("ghost") != std::string::npos)
			this->_db->deleteUser(username);
		this->_clients.erase(username);
	}
}

Message* Server::addMessageToMessagesQueue(std::string allMsg, SOCKET socket, int port)
{
	Message* msg = new Message(allMsg);
	std::unique_lock<std::mutex> lock(this->_messagesMutex);
	this->_messagesQueue.push(*new std::pair<SOCKET, Message>(socket, *msg));
	lock.unlock();
	this->_messagesCv.notify_one();
	return msg;
}

void Server::addSecondaryServer(SOCKET socket, int id)
{
	std::unique_lock<std::mutex> lock(this->_secondaryServersMu);
	this->_secondaryServers.push_back(new SecondaryServer(socket, id));
	lock.unlock();
	this->_messagesCv.notify_one();
}
