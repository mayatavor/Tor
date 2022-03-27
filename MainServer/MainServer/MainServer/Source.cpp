#include <iostream>
#include "WSAInitializer.h"
#include "Server.h"
#include "MessageType.h"
#include <list>
#include "User.h"
#include "RSAencryption.h"

int main()
{
	DatabaseAccess* db = new DatabaseAccess();
	db->open();
	
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		/*std::vector<std::string> args = { "username", "password", "127.0.1.1", "5755" };
		Message* m = myServer.caseLogin(args);*/
		myServer.serve(5678);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	//7 14279

	//std::string enc = RSAencryption::EncryptRSA("H", 3, 3127);
	//std::cout << enc << std::endl;


	system("PAUSE");
	return 0;
}


