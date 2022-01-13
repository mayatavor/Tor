#include "serialize.h"
#include "Structs.h"
#include <iostream>

#define IN_USER_DELIMITER "::::"
#define BETWEEN_USERS_DELIMITER "~"

std::vector<std::string> serialize::serializeUsers(std::list<std::string> allUsers, std::list<std::string> favorites)
{
    std::list<std::string>::iterator it;
    std::list<UsersListItem> users;
    for (it = allUsers.begin(); it != allUsers.end(); it++) {
            UsersListItem uli;
            uli.isFavorite = false;
            uli.usernameOther = *it;
            uli.isGhost = (*it).find("ghost") != std::string::npos;
        if (std::find(favorites.begin(), favorites.end(), *it) != favorites.end()) {
            //bool isGhost = (*it).find("ghost") != std::string::npos;
            uli.isFavorite = true;
        }
            users.push_back(uli);
    }
    std::list<UsersListItem>::iterator usersIt;
    std::vector<std::string> msg;
    for (usersIt = users.begin(); usersIt != users.end(); usersIt++) {
        std::string user = (*usersIt).usernameOther + IN_USER_DELIMITER + std::to_string((*usersIt).isFavorite) + IN_USER_DELIMITER + std::to_string((*usersIt).isGhost) + BETWEEN_USERS_DELIMITER;
        //message += user;
        msg.push_back(user);
    }
    std::string lastUser = msg[msg.size() - 1];
    msg[msg.size() - 1] = lastUser.substr(0, lastUser.length() - 1);
    //message = message.substr(0, message.length() - 1);
    return msg;
}

std::vector<std::string> serialize::serializeChatHistory(std::list<MessagesListItem> messages)
{
    std::vector<std::string> result;
    for (auto it = messages.begin(); it != messages.end(); it++)
    {
        std::string msg = it->username + IN_USER_DELIMITER + it->msg;
        result.push_back(msg);
    }
    return result;
}
