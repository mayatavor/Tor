#pragma once

enum MessageType
{
	secondaryServerConnected = 100,
	logIn = 101,
	signUp = 102,
	logout = 212,
	sendUserLeft = 121,
	ghostLogIn = 103,
	sendChatMessage = 300,
	getChatHistory = 301,
	getUsers = 302,
	getUsersWhenJoined = 320,
	getUsersWhenLeft = 230,
	sendMessageToOtherUser = 303,
	error = 400,
	success = 200,
	ghostName = 201,
	favoriteUser = 110,
	removeFavoriteUser = 111,
	/*userAlreadyExists = 402,*/
};