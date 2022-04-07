#include "DatabaseAccess.h"
#include <ctime>
#include <list>
#include <io.h>
#include <map>

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
		try
		{
			if (!createDBstructure())
				return false;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		//std::string key = "swordfish";
		const char* key = "swordfish123";
		int res1 = sqlite3_key(this->_db, key, 12);
		if (res1 != SQLITE_OK) {
			std::cout << "wrong key" << std::endl;
			return false;
		}
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
		else if (std::string(azColName[i]) == "port")
			user.setPort(std::atoi(argv[i]));
	}
	users->push_back(user);
	return 0;
}


bool DatabaseAccess::createUser(std::string username, std::string password, std::string ip, std::string port)
{
	std::string str = "INSERT INTO Users (username, password, ipAddress, port) VALUES('" + username + "', '" + password + "', '" + ip + "', " + port + ");";
	try
	{
		exec(str.c_str(), nullptr, nullptr);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

void DatabaseAccess::deleteUser(const std::string& username)
{
	std::string str = "DELETE FROM Users WHERE username = '" + username + "';";
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

std::string DatabaseAccess::getUsernameById(int id)
{
	std::list<User> users;
	std::string str = "SELECT * FROM Users WHERE userId = " + std::to_string(id) + ";";
	exec(str.c_str(), getUsersCallback, &users);
	if (!users.empty())
		return (*users.begin()).getUsername();
	else
		return NULL;
}

void DatabaseAccess::updateUsersDetails(std::string username, std::string ip, std::string port)
{
	std::string str = "UPDATE Users SET ipAddress = '" + ip + "', port = " + port + " WHERE username='" + username + "';";
	try
	{
		exec(str.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int getUsersNames(void* data, int argc, char** argv, char** azColName)
{
	std::list<std::string>* users = (std::list<std::string>*)data;
	User user;
	for (int i = 0; i < argc; i++) {
		users->push_back(argv[0]);		
	}
	return 0;
}


std::list<std::string> DatabaseAccess::getUsers()
{
	std::string statement = "SELECT username FROM Users;";
	std::list<std::string> users;
	try
	{
		exec(statement.c_str(), getUsersNames, &users);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return users;
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
	if (!chats.empty())
		return *chats.begin();
	else
		return Chat();
}
Chat DatabaseAccess::getChatByUsers(std::string firstUser, std::string secondUser)
{
	User user1 = getUser(firstUser);
	User user2 = getUser(secondUser);
	std::string statement = "SELECT * FROM Chats WHERE ((firstUserId = " + std::to_string(user1.getId())  + " AND secondUserId = " + std::to_string(user2.getId()) + ") OR (firstUserId = " + std::to_string(user2.getId()) + " AND secondUserId = " + std::to_string(user1.getId())  + "));";
	std::list<Chat> chats;
	try
	{
		exec(statement.c_str(), getChatsCallback, &chats);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	if (!chats.empty())
		return *chats.begin();
	else
		return Chat();
}
bool DatabaseAccess::addFavorite(std::string addsUsername, std::string usernameToAdd)
{
	User u = getUser(addsUsername);
	Chat chat = getChatByUsers(addsUsername, usernameToAdd);
	std::string statement = "INSERT INTO Favorites (userId, chatId) VALUES(" + std::to_string(u.getId()) + ", " + std::to_string(chat.getChatId()) + ");";
	try
	{
		exec(statement.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}


int getFavoritesUsernames(void* data, int argc, char** argv, char** azColName)
{
	std::list<std::string>* usernames = (std::list<std::string>*)data;
	for (int i = 0; i < argc; i++) {
		usernames->push_back(std::string(argv[0]));
	}
	return 0;
}

std::list<std::string> DatabaseAccess::getFavoritesOfUser(std::string username)
{
	std::list<std::string> usernames;
	User u = getUser(username);
	//std::string statement = "select chats.firstUserId, chats.secondUserId FROM Favorites INNER JOIN Chats on Favorites.chatId=chats.chatId WHERE Favorites.userId=" + std::to_string(u.getId()) + ";" ;
	/*std::string statement = "SELECT \
		CASE WHEN chats.firstUserId = " + std::to_string(u.getId()) + "THEN secondUserId \
		ELSE firstUserId END\
		AS user \
		FROM chats\
		WHERE chats.chatId\
		IN(\
			SELECT Favorites.chatId\
			from Favorites\
		); ";*/

	std::string statement = "with query_1 AS (SELECT CASE WHEN chats.firstUserId =" + std::to_string(u.getId()) + " THEN secondUserId ELSE firstUserId END AS user FROM chats WHERE chats.chatId IN(SELECT Favorites.chatId from Favorites)) SELECT Users.username FROM query_1 INNER JOIN Users ON Users.userId = user; ";
	try
	{
		exec(statement.c_str(), getFavoritesUsernames, &usernames);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return usernames;
}

bool DatabaseAccess::removeFavorite(std::string username, std::string usernameToRemove)
{
	User u = getUser(usernameToRemove);      //userId && chatID
	Chat chat = getChatByUsers(username, usernameToRemove);
	std::string statement = "DELETE FROM Favorites WHERE UserID = " + std::to_string(u.getId()) + " AND ChatId = " + std::to_string(chat.getChatId()) + ";";
	try
	{
		exec(statement.c_str(), nullptr, nullptr);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

int isFavoriteCallback(void* data, int argc, char** argv, char** azColName)
{
	int* count = (int*)data;
	*count = std::atoi(argv[0]);
	return 0;
}

bool DatabaseAccess::isFavorite(std::string username1, std::string username2)
{
	int count = 0;
	std::string statement = "with q1 as \
		(select chatId as chatId\
			from chats\
			where(firstUserId IN(select users.UserId as firstUserId from users where users.username = '" + username1 + "')\
				and secondUserId IN(select users.UserId as secondUserId from users where users.username = '" + username2 +"'))\
			OR(firstUserId IN(select users.UserId as secondUserId from users where users.username = '" + username2 + "')\
				and secondUserId IN(select users.UserId as firstUserId from users where users.username = '" + username1 + "')))\
		select count(favorites.chatId) from favorites where favorites.chatId in(select chatId from q1); ";

	try
	{
		exec(statement.c_str(), &isFavoriteCallback, &count);
		return count;
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

bool DatabaseAccess::addMessage(std::string msgContent, int chatId, int senderId)
{
	std::time_t timestamp = std::time(nullptr);
	long int t = static_cast<long int>(timestamp);
	std::string statement = "INSERT INTO Messages (chatId, senderId, messageContent) VALUES (" + std::to_string(chatId) + ", " + std::to_string(senderId) + ", '" + msgContent + "');";
	try
	{
		exec(statement.c_str(), nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

int getChatHistoryCallback(void* data, int argc, char** argv, char** azColName) 
{
	std::list<MessagesListItem>* mesages = (std::list<MessagesListItem>*)data;
	MessagesListItem message;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "messageContent") {
			message.msg = argv[i];
		}
		else if (std::string(azColName[i]) == "senderId") {
			message.id = argv[i];
		}
	}
	mesages->push_back(message);
	return 0;
}

std::list<MessagesListItem> DatabaseAccess::getChatHistory(int chatId)
{
	std::list<MessagesListItem> messages;
	std::string statement = "SELECT messageContent, senderId from Messages WHERE chatId = " + std::to_string(chatId) + ";";
	try
	{
		exec(statement.c_str(), getChatHistoryCallback, &messages);
		for (auto it = messages.begin(); it != messages.end(); it++) {
			it->username = this->getUsernameById(std::stoi(it->id));
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return messages;
}


bool DatabaseAccess::createDBstructure()
{
	char usersTable[] = "CREATE TABLE IF NOT EXISTS Users(userId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, password TEXT, ipAddress TEXT NOT NULL, port INTEGER DEFAULT 0); ";
	char SecondaryServersTable[] = "CREATE TABLE IF NOT EXISTS SecondaryServers(serverID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ipAddress TEXT NOT NULL, password TEXT NOT NULL, d INTEGER NOT NULL, e INTEGER NOT NULL); ";
	char chatsTable[] = "CREATE TABLE IF NOT EXISTS Chats(chatId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, firstUserId INTEGER NOT NULL, secondUserId INTEGER NOT NULL, FOREIGN KEY(firstUserId) REFERENCES Users(userId) ON DELETE CASCADE, FOREIGN KEY(secondUserId) REFERENCES Users(userId) ON DELETE CASCADE);";
	char FavoritesTable[] = "CREATE TABLE IF NOT EXISTS Favorites(userId INTEGER NOT NULL, chatId INTEGER NOT NULL, FOREIGN KEY(userId) REFERENCES Users(userId), FOREIGN KEY(chatId) REFERENCES Chats(chatId) ON DELETE CASCADE);";
	char MessagesTable[] = "CREATE TABLE IF NOT EXISTS Messages(messageId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, chatId INTEGER NOT NULL, messageContent TEXT NOT NULL, senderId INTEGER NOT NULL, FOREIGN KEY(chatId) REFERENCES Chats(chatId) ON DELETE CASCADE, FOREIGN KEY(senderId) REFERENCES Users(userId) ON DELETE CASCADE);";
	try
	{
		exec(usersTable, nullptr, nullptr);
		exec(SecondaryServersTable, nullptr, nullptr);
		exec(chatsTable, nullptr, nullptr);
		exec(FavoritesTable, nullptr, nullptr);
		exec(MessagesTable, nullptr, nullptr);

		const char* key = "swordfish";
		int res1 = sqlite3_rekey(this->_db, key, 9);
		
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
	else
		return true;
}
