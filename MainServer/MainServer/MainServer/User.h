#pragma once
#include <string>


class User
{
public:
	User();
	User(int id, std::string username, std::string password, std::string ipAddress, int port);

	//getters
	int getId() const;
	const std::string& getUsername() const;
	const std::string& getPassword() const;
	const std::string& getIp() const;
	const int getPort();

	//setters
	void setId(int id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setIpAddress(const std::string& ip);
	void setPort(const int& port);

private:
	int _userId;
	std::string _username;
	std::string _password;
	std::string _ipAddress;
	int _port;
};

