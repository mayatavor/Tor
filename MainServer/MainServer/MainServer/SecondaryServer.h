#pragma once
#include <WinSock2.h>
#include <Windows.h>

class SecondaryServer
{
public:
	SecondaryServer(SOCKET socket, int id); //Ctor
	~SecondaryServer() = default; //Detor

	const int getId();
	const SOCKET getSocket();


private:
	int _id;
	SOCKET _socket;
};

