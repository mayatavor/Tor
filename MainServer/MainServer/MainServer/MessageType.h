#pragma once

enum MessageType
{
	secondaryServerConnected = 100,
	logIn = 101,
	signIn = 102,
	ghostLogIn = 103,
	sendChatMessage = 200,
	wrongPasswordLogin = 400,
	userDoesntExist = 401,
};