#include "Chat.h"

Chat::Chat(int firstUserId, int secondUserId)
{
	this->_firstUser = firstUserId;
	this->_secondUser = secondUserId;
}

int Chat::getChatId() const
{
	return this->_chatId;
}

int Chat::getFirstuserId() const
{
	return this->_firstUser;
}

int Chat::getSecondUserId() const
{
	return this->_secondUser;
}

void Chat::setChatId(int chatId)
{
	this->_chatId = chatId;
}

void Chat::setFirstuser(int id)
{
	this->_firstUser = id;
}

void Chat::setSecondUser(int id)
{
	this->_secondUser = id;
}
