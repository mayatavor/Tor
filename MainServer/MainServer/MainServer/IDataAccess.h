#pragma once
#include "User.h"

class IDataAccess
{
public:
	virtual ~IDataAccess() = default;

	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;

	//users
	virtual void createUser(std::string username, std::string password, std::string ip, std::string port) = 0;
	virtual void deleteUser(const int& userId) = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual User getUser(const std::string& username) = 0;
	virtual void updateUsersIpAndPort(std::string usrname, std::string ip, std::string port) = 0;
	

private:

};

