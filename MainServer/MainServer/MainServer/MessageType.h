#pragma once

enum MessageType
{
	secondaryServerConnected = 100,
	logIn = 101,
	signUp = 102,
	logout = 212,
	ghostLogIn = 103,
	sendChatMessage = 300,
	error = 400,
	success = 200,
	ghostName = 201,
	favoriteUser = 110,
	/*userAlreadyExists = 402,*/
};