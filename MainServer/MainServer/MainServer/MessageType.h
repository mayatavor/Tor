#pragma once

enum MessageType
{
	secondaryServerConnected = 100,
	logIn = 101,
	signUp = 102,
	logout = 212,
	ghostLogIn = 103,
	sendChatMessage = 300,
	getChatHistory = 301,
	error = 400,
	success = 200,
	ghostName = 201,
	favoriteUser = 110,
	removeFavoriteUser = 111,
	getUsers = 302,
	/*userAlreadyExists = 402,*/
};