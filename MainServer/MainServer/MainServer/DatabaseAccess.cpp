#include "DatabaseAccess.h"
#include <io.h>
#include <list>

bool DatabaseAccess::open()
{
	int doesFileExist = _access(DB_FILE_NAME.c_str(), 0); //Checks if the database exists.

	int res = sqlite3_open(DB_FILE_NAME.c_str(), &this->_db);

	if (res != SQLITE_OK) {
		_db = nullptr;
		std::cout << "Faild to open DB" << std::endl;
		return false;
	}


	if (doesFileExist == -1) {
		if (!createDBstructure())
			return false;
	}

	return true;
}

void DatabaseAccess::close()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}

void DatabaseAccess::clear()
{
	char sqlStatement1[] = "DELETE FROM Users; ";
	char sqlStatement2[] = "DELETE FROM SecondaryServers; ";
	char sqlStatement3[] = "DELETE FROM Chats; ";
	char sqlStatement4[] = "DELETE FROM Favorites; ";

	try
	{
		exec(sqlStatement1);
		exec(sqlStatement2);
		exec(sqlStatement3);
		exec(sqlStatement4);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


int getUsersCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<User>* users = (std::list<User>*)data;
	User user;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "userId") 
			user.setId(std::atoi(argv[i]));
		else if (std::string(azColName[i]) == "username") 
			user.setUsername(argv[i]);
		else if (std::string(azColName[i]) == "password") 
			user.setPassword(argv[i]);
		else if (std::string(azColName[i]) == "ipAddress")
			user.setIpAddress(argv[i]);
	}
	users->push_back(user);
	return 0;
}


void DatabaseAccess::createUser(const User& user)
{
	std::string str = "INSERT INTO Users (username, password, ipAddress) VALUES('" + user.getUsername() + "', '" + user.getPassword() + "', '" + user.getIp() + "');";
	try
	{
		exec(str.c_str());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void DatabaseAccess::deleteUser(const int& userId)
{
	std::string str = "DELETE FROM Users WHERE userID = " + std::to_string(userId) + ";";
	try
	{
		exec(str.c_str());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool DatabaseAccess::doesUserExist(const int& userId)
{
	User user = getUser(userId);
	if (user.getId() == 0)
		return false;
	return true;
}

User DatabaseAccess::getUser(const int& userId)
{
	std::list<User> users;
	std::string str = "SELECT * FROM Users WHERE ID = " + std::to_string(userId) + ";";
	const char* sqlStatement = str.c_str();
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement, getUsersCallback, &users, errMessage);
	if (res != SQLITE_OK)
		std::cout << "Something went wrong" << std::endl;
	if (!users.empty())
		return *users.begin();
	else
		return User();
}

bool DatabaseAccess::createDBstructure()
{
	char statement1[] = "CREATE TABLE IF NOT EXISTS Users(userId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, password TEXT NOT NULL, ipAddress TEXT NOT NULL); ";
	char statement2[] = "CREATE TABLE IF NOT EXISTS SecondaryServers(serverID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ipAddress TEXT NOT NULL, password TEXT NOT NULL, d INTEGER NOT NULL, e INTEGER NOT NULL); ";
	char statement3[] = "CREATE TABLE IF NOT EXISTS Chats(chatId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, firstUserId INTEGER NOT NULL, secondUSerId INTEGER NOT NULL); ";
	char statement4[] = "CREATE TABLE IF NOT EXISTS Favorites(userId INTEGER NOT NULL, chatId INTEGER NOT NULL); ";
	try
	{
		exec(statement1);
		exec(statement2);
		exec(statement3);
		exec(statement4);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return false;
}

bool DatabaseAccess::exec(const char* sqlStatement)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(_db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		throw("Failed to execute the query");
	return true;
}
