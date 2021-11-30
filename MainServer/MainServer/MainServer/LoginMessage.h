#pragma once
#include <string>
#include "Message.h"

class LoginMessage : public Message
{
public:
	LoginMessage(int code, SOCKET userSocket, std::string username, std::string password, std::string ip, int port);
	~LoginMessage() = default;

	std::string& getUsername();
	std::string& getPassword();
	std::string& getIp() ;
	int& getPort() ;

private:
	std::string _username;
	std::string _password;
	std::string _ip;
	int port;
};

