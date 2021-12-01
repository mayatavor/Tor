#include "Server.h"
#include "MessageType.h"
#include "DatabaseAccess.h"

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
	this->_db->createUser(args[0], args[1], args[2],args[3]);
	std::vector<std::string> answerArgs = { "SignedUp Successfully" };
	return new Message(success, answerArgs);
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
			case logIn:
				msg = caseLogin(args);
				break;
			case signUp:
				msg = caseSignUp(args);
				break;

			default:
				break;
			}
			if(msg)
				h.sendData(m.first, msg->buildMessage());
		}

		//if (m.getCode() == USER_LOGGED_IN) {
		//	
		//}

		//int len = m.GetMessageContent().length();
		//std::string msg = "200" + len + m.GetMessageContent();
		//h.sendData(m.getSocket(), msg);
		////this->_clients.insert(std::pair<std::string, SOCKET>("", m.getSocket())); ///if login or signUpMessage
	}
}

void Server::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	std::thread t(&Server::clientHandler, this, client_socket);
	t.detach();
}

void Server::clientHandler(SOCKET socket)
{
	try
	{
		Helper h;
		while (true)
		{
			/*int code = h.getIntPartFromSocket(socket, 3);
			if (code == SECONDARY_SERVER_CONNECTED)
			{
				int len = h.getIntPartFromSocket(socket, 2);
				int serverId = h.getIntPartFromSocket(socket, len);
				addSecondaryServer(socket, serverId);
			}
			else if(code == SEND_MESSAGE)
			{
				int len = h.getIntPartFromSocket(socket, 3);
				std::string msg = h.getStringPartFromSocket(socket, len);
				addMessageToMessagesQueue(SEND_MESSAGE, "", "", msg, socket);
			}*/
			int len = h.getIntPartFromSocket(socket, 3);
			std::string message = h.getStringPartFromSocket(socket, len);
			addMessageToMessagesQueue(message, socket);
		}
	}
	catch (const std::exception& e)
	{
		/*std::unique_lock<std::mutex> lock(this->_messagesMutex);
		this->_messagesQueue.push(*new Message(-1, "", "", "", socket));
		lock.unlock();
		this->_messagesCv.notify_one();*/
		std::cout << e.what() << std::endl;
	}
}

void Server::addMessageToMessagesQueue(std::string allMsg, SOCKET socket)
{
	std::unique_lock<std::mutex> lock(this->_messagesMutex);
	//this->_messagesQueue.push(*new Message(code, sender, reciever, content, clientSocket));
	this->_messagesQueue.push(*new std::pair<SOCKET, Message>(socket, *new Message(allMsg)));
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
