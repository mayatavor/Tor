#include "CommunicationWithSecondaryServers.h"
//#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <WinSock2.h>
#include <sys/types.h>

CommunicationWithSecondaryServers::CommunicationWithSecondaryServers()
{
}

CommunicationWithSecondaryServers::~CommunicationWithSecondaryServers()
{
}

void CommunicationWithSecondaryServers::func(int port)
{
	int connfd;
	//struct sockaddr_in servaddr, cli;

	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cout << "Socket connection failed :(" << std::endl;
		exit(0);
	}
	else
		std::cout << "Socket created Successfully" << std::endl;

	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	/*
	* struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    //
	*/
	//_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	if (connect(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR) {
		std::cout << "Connection with server failed :(" << std::endl;
		exit(0);
	}
	else
		std::cout << "Connection to sever was successful" << std::endl;
}
