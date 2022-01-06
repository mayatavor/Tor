#pragma once
#include "Structs.h"
#include <string>
#include <vector>
#include <list>

class serialize
{
public:
	/*
	* The function gets a list of the favorites users and a list of all of the users and returns a serialized string of the users.
	* input: List of all of the users and a list of the favorites users.
	* output: The serialised string of the users.
	*/
	static std::vector<std::string> serializeUsers(std::list<std::string> allUsers, std::list<std::string> favorites);

	/*
	* The function gets a list that reporesent all the messags in a chat and returns a string that reporesents those messages.
	* input: The list of the messages.
	* ouptu: String that represents the given messages.
	*/
	static std::vector<std::string> serializeChatHistory(std::list<MessagesListItem> messages);
};

