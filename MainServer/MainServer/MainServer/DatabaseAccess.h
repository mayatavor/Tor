#pragma once
#include "IDataAccess.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

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
	void createUser(const User& user);
	void deleteUser(const int& userId);
	bool doesUserExist(const int& userId);
	User getUser(const int& userId);

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
	bool exec(const char* sqlStatement);
};

