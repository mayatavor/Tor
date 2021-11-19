#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <map>

class Server
{
public:
	Server();  //Ctor
	~Server(); //Detor

	void serve(int port);

private:
	std::map<std::string, SOCKET> _clients;
	void accept();
};

