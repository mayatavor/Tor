#pragma once
#include <string>

struct UsersListItem
{
	std::string usernameOther;
	bool isFavorite;
	bool isGhost;
};

struct MessagesListItem
{
	std::string usernameOther;
	std::string msg;
};
