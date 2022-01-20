#pragma once
#include "Structs.h"
#include "User.h"
#include "Chat.h"
#include <list>

class IDataAccess
{
public:
	virtual ~IDataAccess() = default;

	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;

	//users
	virtual bool createUser(std::string username, std::string password, std::string ip, std::string port) = 0;
	virtual void deleteUser(const int& userId) = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual User getUser(const std::string& username) = 0;
	virtual void updateUsersIpAndPort(std::string usrname, std::string ip, std::string port) = 0;


	//SecondaryServers


	//Chats
	virtual std::list<Chat> getChats() = 0;
	virtual void createChat(int firstUserId, int secondUserId) = 0;
	virtual Chat getChat(int chatId) = 0;
	virtual Chat getChatByUsers(std::string firstUser, std::string secondUser) = 0;


	//Messages
	virtual bool addMessage(std::string msgContent, int chatId, int senderId) = 0;
	virtual std::list<MessagesListItem> getChatHistory(int chatId) = 0;


	//Favorites
	virtual bool addFavorite(std::string addsUsername, std::string usernameToAdd) = 0;
	//virtual std::list<

};

