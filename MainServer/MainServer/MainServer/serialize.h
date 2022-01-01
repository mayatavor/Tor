#pragma once
#include <string>
#include <list>
#include <vector>

class serialize
{
public:
	/*
	* The function gets a list of the favorites users and a list of all of the users and returns a serialized string of the users.
	* input: List of all of the users and a list of the favorites users.
	* output: The serialised string of the users.
	*/
	static std::vector<std::string> serializeUsers(std::list<std::string> allUsers, std::list<std::string> favorites);


};

