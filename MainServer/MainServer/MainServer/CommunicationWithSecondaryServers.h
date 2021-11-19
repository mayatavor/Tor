#pragma once
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <mutex>
#include <list>

class CommunicationWithSecondaryServers
{
public:
	CommunicationWithSecondaryServers();
	~CommunicationWithSecondaryServers();
	void func(int port);
private:
	std::list<SOCKET> secondarySockets;

};

