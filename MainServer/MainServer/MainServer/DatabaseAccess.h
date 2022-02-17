#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include "Structs.h"

const std::string DB_FILE_NAME = "TorDb.sqlite";

class DatabaseAccess : public IDataAccess
{
public:
	DatabaseAccess() = default;
	~DatabaseAccess() = default;

	bool open();   //Opens the Database.
	void close();  //Closes the Database.
	void clear();  //Cleans all the was saved in the DB


	//users
	//void createUser(const User& user);

	/*
	* The function adds a user to the users table in the DB.
	* input: The user's username, password, ip and port.
	* output: True if the user created successflly and false if not.
	*/
	bool createUser(std::string username, std::string password, std::string ip, std::string port);
	void deleteUser(const std::string& username);
	bool doesUserExist(const std::string& username);
	User getUser(const std::string& username);
	std::string getUsernameById(int id);
	void updateUsersIpAndPort(std::string usrname, std::string ip, std::string port);
	//The function returns list of all of the users
	std::list<std::string> getUsers();
	
	//std::list<UsersListItem> getUserToSend(std::string username);


	//chats
	std::list<Chat> getChats();
	void createChat(int firstUserId, int secondUserId);
	Chat getChat(int chatId);
	//The function gets two usernames and returns the chat id that belongsto these users.
	Chat getChatByUsers(std::string firstUser, std::string secondUser); ////Needs to be checked - not sure that working correctlly.
	

	//Favorites
	//The function adds a row to the favorites table.
	bool addFavorite(std::string addsUsername, std::string usernameToAdd);
	//The function returns a list of all the usernamames that the user marked as favortites.
	std::list<std::string> getFavoritesOfUser(std::string username);
	//The function remvoes a specific row from the favorites table.
	bool removeFavorite(std::string username, std::string usernameToRemove);
	//The function returns true is username2 is in the favorites of username1, else it returns false.
	bool isFavorite(std::string username1, std::string username2);


	//Messages 
	//The function adds a message to the messages table, it returns true if th message was added successfully and false if not.
	bool addMessage(std::string msgContent, int chatId, int senderId) ;
	/*
	* The function reuturns a list of all of the messages in a chat.
	* input: The ID of the chat,
	* output: List of the messageds.
	*/
	std::list<MessagesListItem> getChatHistory(int chatId);

private:
	sqlite3* _db;

	/*
	* The function creates the tables in the DB;
	* input: none
	* output: True if the creation succeded, false if not.
	*/
	bool createDBstructure();

	/*
	* The functinon gets the sql statement and calls to sqlite3_exec to perfrom the suitable sql function.
	* input: The sql statement
	* output: True if the query succeeded, false if not.
	*/
	bool exec(const char* sqlStatement, int(*callback)(void*, int, char**, char**), void* data);
};

