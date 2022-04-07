#pragma once
#include "MessageType.h"
#include <vector>
#include <string>
#include <numeric>
#define DELIMITER "~"


class Message
{
public:
	Message(std::string allMsg);
	Message(MessageType type, std::vector<std::string> args);
	Message(std::string allMsg, int key);
	~Message() = default;

	std::vector<std::string> getArgs() const;
	MessageType getMessageType() const;
	bool validateArgumentLength();
	std::string buildMessage(int key);
	std::string encryptAndDecrypt(int key, std::string msg);

private:
	MessageType _mt;
	std::vector<std::string> _args;

};
