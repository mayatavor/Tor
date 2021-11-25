#include <iostream>
#include "WSAInitializer.h"
#include "Server.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.serve(5678);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}
