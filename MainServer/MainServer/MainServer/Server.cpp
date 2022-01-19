#include "Server.h"
#include "MessageType.h"
#include "serialize.h"
#include "Structs.h"
#include <iostream>
#include <stdlib.h>
#include "Helper.h"
#include <stdio.h>
#include <time.h>
#include <thread>
#include "User.h"

#define USER_EXISTS(id, content, existsOrNot) \
 if (this->_db->doesUserExist(id) == existsOrNot)\
{ \
	std::vector<std::string> msg = { content }; \
	return new Message(error, msg); \
}

Server::Server()
{
	this->_db = new DatabaseAccess();
	this->_db->open();
	srand(time(0));
	
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

Message* Server::caseLogin(std::vector<std::string> args)
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
	this->_db->updateUsersIpAndPort(args[0], args[2], args[3]);
	return new Message(success, { "LoggedIn successfully" });
}

Message* Server::caseSignUp(std::vector<std::string> args)
{
	if (this->_db->doesUserExist(args[0]))
	{
		std::vector<std::string> msg = { "User with this usename already exists" };
		return new Message(error, msg);
	}
	//USER_EXISTS(args[0], "User with this usename already exists", true);
	if (this->_db->createUser(args[0], args[1], args[2], args[3])) {

		std::vector<std::string> answerArgs = { "SignedUp Successfully" };
		return new Message(MessageType::success, answerArgs);
	}
	else {
		std::vector<std::string> answerArgs = { "Error accurd while singing up" };
		return new Message(MessageType::error, answerArgs);
	}
}

Message* Server::caseGhostLogin(std::vector<std::string> args)
{
	int ghostIdentifier = rand();
	std::string username = "ghost" + std::to_string(ghostIdentifier);
	std::vector<std::string> answerArgs;
	if (this->_db->createUser(username, "", args[2], args[3]))
	{
		answerArgs.push_back("Ghost user logged in successfully");
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
	USER_EXISTS(args[0], "User doesn't exist", false);
	std::map<std::string, SOCKET>::iterator it = this->_clients.find(args[0]);
	if (it == this->_clients.end()) {
		std::vector<std::string> msg = { "User doesn't connected so he can't be logged out" };
		return new Message(error, msg);
	}
	this->_clients.erase(it);
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


//Message* Server::getFavorites(std::vector<std::string> args)
//{
//	
//	/*if (!this->_db->doesUserExist(args[0])) {
//		std::vector<std::string> msg = { "User doesn't exist" };
//		return new Message(error, msg);
//	}*/
//	this->_db->getFavoritesOfUser(args[0]);
//	std::list<std::string> usersList = this->_db->getUsers();
//}


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
				msg = caseLogin(args);
				break;
			case MessageType::signUp:
				msg = caseSignUp(args);
				break;
			case MessageType::ghostLogIn:
				msg = caseGhostLogin(args);
				break;
			case MessageType::logout:
				msg = caseLogout(args);
				break;
			case MessageType::favoriteUser:
				msg = caseAddFavorites(args);
			case MessageType::getUsers:
				msg = caseGetUsers(args);
				break;
			case MessageType::sendChatMessage:
				msg = caseSendMessage(args);
				break;
			case MessageType::getChatHistory:
				msg = caseGetChatHistory(args);

			default:
				break;
			}
			if(msg)
				h.sendData(m.first, msg->buildMessage());
		}
		delete msg;
	}
}


Message* Server::caseGetUsers(std::vector<std::string> args)
{
	std::list<std::string> allUsers = this->_db->getUsers();
	std::list<std::string> favorites = this->_db->getFavoritesOfUser(args[0]);
	std::vector<std::string> msg = serialize::serializeUsers(allUsers, favorites);
	return new Message(MessageType::getUsers, msg);
}

Message* Server::caseSendMessage(std::vector<std::string> args)
{
	User u1 = this->_db->getUser(args[0]);
	User u2 = this->_db->getUser(args[1]);
	std::vector<std::string> msg;
	if (u1.getId() == -1 || u2.getId() == -1)
	{
		msg.push_back("One of the users doesn't exist");
		return new Message(MessageType::error, msg);
	}
	Chat chat = this->_db->getChatByUsers(args[0], args[1]);
	if (chat.getChatId() == -1) 
		this->_db->createChat(u1.getId(), u2.getId());
	chat = this->_db->getChatByUsers(args[0], args[1]);
	bool success = this->_db->addMessage(args[2], chat.getChatId(), std::stoi(args[0]));
	if (success) {
		msg.push_back("Message added successfully");
		std::vector<std::string> msgToUser = { args[2] };
		Message* msgToOtherClient = new Message(MessageType::sendMessageToOtherUser, msgToUser);
		SOCKET otherUserSock = this->_clients[args[1]];
		Helper::sendData(otherUserSock, msgToOtherClient->buildMessage());
		delete msgToOtherClient;
		return new Message(MessageType::success, msg);
	}
	else
	{
		msg.push_back("Couldn't add mesage:(");
		return new Message(MessageType::success, msg);
	}
}

Message* Server::caseGetChatHistory(std::vector<std::string> args)
{
	Chat chat = this->_db->getChatByUsers(args[0], args[1]);
	std::list<MessagesListItem> messages = this->_db->getChatHistory(chat.getChatId());
	std::vector<std::string> msg = serialize::serializeChatHistory(messages);
	return new Message(MessageType::success, msg);
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
	try
	{
		Helper h;
		while (true)
		{
			int len = h.getIntPartFromSocket(socket, 5);
			std::string message = h.getStringPartFromSocket(socket, len);
			addMessageToMessagesQueue(message, socket, port);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Server::addMessageToMessagesQueue(std::string allMsg, SOCKET socket, int port)
{
	std::unique_lock<std::mutex> lock(this->_messagesMutex);
	this->_messagesQueue.push(*new std::pair<SOCKET, Message>(socket, *new Message(allMsg, port)));
	lock.unlock();
	this->_messagesCv.notify_one();
}

void Server::addSecondaryServer(SOCKET socket, int id)
{
	std::unique_lock<std::mutex> lock(this->_secondaryServersMu);
	this->_secondaryServers.push_back(new SecondaryServer(socket, id));
	lock.unlock();
	this->_messagesCv.notify_one();
}
