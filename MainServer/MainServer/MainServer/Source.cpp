#include <iostream>
#include "WSAInitializer.h"
#include "Server.h"
#include "MessageType.h"
#include <list>
#include "User.h"

int main()
{

	DatabaseAccess* db = new DatabaseAccess();
	db->open();
	db->createChat(1, 1);
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		std::vector<std::string> args = { "username", "password", "127.0.1.1", "5755" };
		Message* m = myServer.caseLogin(args);
		myServer.serve(5678);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	//std::vector<std::string> vec = { "username", "password","ip", "port"};
	//Message* newMessage = new Message(logIn, vec);
	//std::string megString = newMessage->buildMessage();
	//std::cout << megString << std::endl;
	//Message* msg = new Message("101≡username≡password≡ip≡port");


	system("PAUSE");
	return 0;
}
