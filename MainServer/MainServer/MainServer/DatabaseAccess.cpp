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
		exec(sqlStatement1, nullptr, nullptr);
		exec(sqlStatement2, nullptr, nullptr);
		exec(sqlStatement3, nullptr, nullptr);
		exec(sqlStatement4, nullptr, nullptr);
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
		/*else if (std::string(azColName[i]) == "port")
			user.setPort(std::atoi(argv[i]));*/
	}
	users->push_back(user);
	return 0;
}


void DatabaseAccess::createUser(std::string username, std::string password, std::string ip, std::string port)
{
	std::string str = "INSERT INTO Users (username, password, ipAddress) VALUES('" + username + "', '" + password + "', '" + ip + "');";
	try
	{
		exec(str.c_str(), nullptr, nullptr);
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
		exec(str.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool DatabaseAccess::doesUserExist(const std::string& username)
{
	User user = getUser(username);
	if (user.getId() == -1)
		return false;
	return true;
}

User DatabaseAccess::getUser(const std::string& username)
{
	std::list<User> users;
	std::string str = "SELECT * FROM Users WHERE username = '" + username + "';";
	exec(str.c_str(), getUsersCallback, &users);
	if (!users.empty())
		return *users.begin();
	else
		return User();
}

void DatabaseAccess::updateUsersIpAndPort(std::string username, std::string ip, std::string port)
{
	std::string str = "UPDATE Users SET ipAddress = '" + ip + "', port = " + port + ";";
	try
	{
		exec(str.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int getChatsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<Chat>* chats = (std::list<Chat>*)data;
	Chat chat;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "chatId")
			chat.setChatId(std::atoi(argv[i]));
		else if (std::string(azColName[i]) == "firstUserId")
			chat.setFirstuser(std::atoi(argv[i]));
		else if (std::string(azColName[i]) == "secondUserId")
			chat.setSecondUser(std::atoi(argv[i]));
	}
	chats->push_back(chat);
	return 0;
}


std::list<Chat> DatabaseAccess::getChats()
{
	std::list<Chat> chats;
	std::string statement = "SELECT * FROM Chats;";
	char* errMessage = nullptr;
	try
	{
		exec(statement.c_str(), getChatsCallback, &chats);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return chats;
}
void DatabaseAccess::createChat(int firstUserId, int secondUserId)
{
	std::string str = "INSERT INTO Chats (firstUserId, secondUserId) VALUES(" + std::to_string(firstUserId) + ", " + std::to_string(secondUserId) + "); ";
	try
	{
		exec(str.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
Chat DatabaseAccess::getChat(int chatId)
{
	return Chat();
}
bool DatabaseAccess::createDBstructure()
{
	char usersTable[] = "CREATE TABLE IF NOT EXISTS Users(userId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, password TEXT NOT NULL, ipAddress TEXT NOT NULL, port INTEGER); ";
	char SecondaryServersTable[] = "CREATE TABLE IF NOT EXISTS SecondaryServers(serverID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ipAddress TEXT NOT NULL, password TEXT NOT NULL, d INTEGER NOT NULL, e INTEGER NOT NULL); ";
	char chatsTable[] = "CREATE TABLE IF NOT EXISTS Chats(chatId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, firstUserId INTEGER NOT NULL, secondUserId INTEGER NOT NULL, FOREIGN KEY(firstUserId) REFERENCES Users(userId), FOREIGN KEY(secondUserId) REFERENCES Users(userId)); ";
	char FavoritesTable[] = "CREATE TABLE IF NOT EXISTS Favorites(userId INTEGER NOT NULL, chatId INTEGER NOT NULL, FOREIGN KEY(userId) REFERENCES Users(useId), FOREIGN KEY(chatId) REFERENCES Chats(chatId)); ";
	char MessagesTable[] = "CREATE TABLE IF NOT EXISTS Messages(messageId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, chatId INTEGER NOT NULL, senderId INTEGER NOT NULL, time INTEGER NOT NULL, FOREIGN KEY(chatId) REFERENCES Chats(chatId), FOREIGN KEY(senderId) REFERENCES Users(userId)); ";
	try
	{
		exec(usersTable, nullptr, nullptr);
		exec(SecondaryServersTable, nullptr, nullptr);
		exec(chatsTable, nullptr, nullptr);
		exec(FavoritesTable, nullptr, nullptr);
		exec(MessagesTable, nullptr, nullptr);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return false;
}

bool DatabaseAccess::exec(const char* sqlStatement, int(*callback)(void*, int, char**, char**), void* data)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(_db, sqlStatement, callback, data, &errMessage);
	if (res != SQLITE_OK)
		throw("Failed to execute the query");
	return true;
}
