#include "User.h"

User::User(int id, std::string username, std::string password, std::string ipAddress)
{
	this->_userId = id;
	this->_username = username;
	this->_password = password;
	this->_ipAddress = ipAddress;
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
