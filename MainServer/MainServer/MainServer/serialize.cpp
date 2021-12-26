#include "serialize.h"
#include "Structs.h"
#include <iostream>

std::string serialize::serializeUsers(std::list<std::string> allUsers, std::list<std::string> favorites)
{
    std::string str = "";
    std::list<std::string>::iterator it;
    for (it = allUsers.begin(); it != allUsers.end(); it++) {
        if (std::find(favorites.begin(), favorites.end(), *it) != favorites.end()) {
            bool isGhost = (*it).find("ghost") != std::string::npos;
            UsersListItem uli;
            uli.isFavorite = true;
            uli.isGhost = isGhost;
            uli.usernameOther = *it;
        }
    }

    //for (int i = 0; i < allUsers.size(); i++) {
    //    if(std::find(favorites.begin(), favorites.end(), allUsers[i]) != )
    //}
}
