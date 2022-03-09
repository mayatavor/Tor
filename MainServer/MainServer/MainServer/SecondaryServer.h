#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <utility>


class SecondaryServer
{
public:
	SecondaryServer();
	SecondaryServer(SOCKET& socket, int& id, std::pair<int, int>& publicKey, int port); //Ctor
	~SecondaryServer() = default; //Detor

	int getId() const;
	SOCKET getSocket() const;
	std::pair<int, int> getPublicKey() const;
	int getPort() const;


private:
	int _id;
	std::pair<int, int> _publicKey;
	SOCKET _socket;
	int _port;
};

