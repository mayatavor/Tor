#include "DatabaseAccess.h"
#include <io.h>

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
}

void DatabaseAccess::clear()
{
}

bool DatabaseAccess::createDBstructure()
{
	char statement1[] = "CREATE TABLE IF NOT EXISTS Users(userId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, password TEXT NOT NULL, ipAddress TEXT NOT NULL); ";
	createTable(statement1);
	char statement2[] = "CREATE TABLE IF NOT EXISTS SecondaryServers(serverID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ipAddress TEXT NOT NULL, password TEXT NOT NULL, d INTEGER NOT NULL, e INTEGER NOT NULL); ";
	createTable(statement2);
	char statement3[] = "CREATE TABLE IF NOT EXISTS Chats(chatId INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, firstUserId INTEGER NOT NULL, secondUSerId INTEGER NOT NULL); ";
	createTable(statement3);
	char statement4[] = "CREATE TABLE IF NOT EXISTS Favorites(userId INTEGER NOT NULL, chatId INTEGER NOT NULL); ";
	createTable(statement4);
}

bool DatabaseAccess::createTable(char* sqlStatement)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(_db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	return true;
}
