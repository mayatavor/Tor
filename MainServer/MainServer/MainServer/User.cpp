#include "User.h"

User::User()
{
	this->_userId = -1;
}

User::User(int id, std::string username, std::string password, std::string ipAddress, int port)
{
	this->_userId = id;
	this->_username = username;
	this->_password = password;
	this->_ipAddress = ipAddress;
	this->_port = port;
}



int User::getId() const
{
	return this->_userId;
}

const std::string& User::getUsername() const
{
	return this->_username;
}

const std::string& User::getPassword() const
{
	return this->_password;
}

const std::string& User::getIp() const
{
	return this->_ipAddress;
}

const int User::getPort()
{
	return this->_port;
}

void User::setId(int id)
{
	this->_userId = id;
}

void User::setUsername(const std::string& username)
{
	this->_username = username;
}

void User::setPassword(const std::string& password)
{
	this->_password = password;
}

void User::setIpAddress(const std::string& ip)
{
	this->_ipAddress = ip;
}

void User::setPort(const int& port)
{
	this->_port = port;
}
