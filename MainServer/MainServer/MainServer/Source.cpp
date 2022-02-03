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

	/*std::vector<std::string> vec = { "username", "password","ip", "port"};
	Message* newMessage = new Message(logIn, vec);
	std::string megString = newMessage->buildMessage();
	std::cout << megString << std::endl;
	Message* msg = new Message("101≡username≡password≡ip≡port");*/


	system("PAUSE");
	return 0;
}



//
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#pragma comment (lib, "Ws2_32.lib")
//#include <iostream>
//#include <string.h>
//#include <sstream>
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//using namespace std;
//
//
//int main()
//{
//	WSAData wsaData;
//	WORD DllVersion = MAKEWORD(2, 1);
//	if (WSAStartup(DllVersion, &wsaData) != 0) {
//		cout << "Winsock Connection Failed!" << endl;
//		exit(1);
//	}
//
//	string getInput = "";
//	SOCKADDR_IN addr;
//	int addrLen = sizeof(addr);
//	IN_ADDR ipvalue;
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	addr.sin_port = htons(80);
//	addr.sin_family = AF_INET;
//
//	SOCKET connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
//		cout << "Connected!" << endl;
//		getline(cin, getInput);
//		exit(0);
//	}
//	else {
//		cout << "Error Connecting to Host" << endl;
//		exit(1);
//	}
//	return 0;
//}



