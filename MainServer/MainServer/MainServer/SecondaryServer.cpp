#include "SecondaryServer.h"

SecondaryServer::SecondaryServer()
{
}

SecondaryServer::SecondaryServer(SOCKET& socket, int& id, std::pair<int, int>& publicKey, int port)
{
	this->_id = id;
	this->_socket = socket;
	this->_publicKey.first = publicKey.first;
	this->_publicKey.second = publicKey.second;
	this->_port = port;
}

int SecondaryServer::getId() const
{
	return this->_id;
}

SOCKET SecondaryServer::getSocket() const
{
	return this->_socket;
}

std::pair<int, int> SecondaryServer::getPublicKey() const
{
	return this->_publicKey;
}

int SecondaryServer::getPort() const
{
	return this->_port;
}
