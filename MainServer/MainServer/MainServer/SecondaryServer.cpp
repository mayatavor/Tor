#include "SecondaryServer.h"

SecondaryServer::SecondaryServer(SOCKET socket, int id)
{
	this->_id = id;
	this->_socket = socket;
}

const int SecondaryServer::getId()
{
	return this->_id;
}

const SOCKET SecondaryServer::getSocket()
{
	return this->_socket;
}
