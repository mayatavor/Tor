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
        if (std::find(favorites.begin(), favorites.end(), *it) != favorites.end()) {
            bool isGhost = (*it).find("ghost") != std::string::npos;
            UsersListItem uli;
            uli.isFavorite = true;
            uli.isGhost = isGhost;
            uli.usernameOther = *it;
            users.push_back(uli);
        }
    }
    std::list<UsersListItem>::iterator usersIt;
    std::string message = "";
    std::vector<std::string> msg;
    for (usersIt = users.begin(); usersIt != users.end(); usersIt++) {
        std::string user = (*usersIt).usernameOther + IN_USER_DELIMITER + std::to_string((*usersIt).isFavorite) + IN_USER_DELIMITER + std::to_string((*usersIt).isGhost) + BETWEEN_USERS_DELIMITER;
        //message += user;
        msg.push_back(user);
    }
    //message = message.substr(0, message.length() - 1);
    return msg;
}
