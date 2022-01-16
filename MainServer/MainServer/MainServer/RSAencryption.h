#pragma once
#include <string>

class RSAencryption
{
public:
	/*
	this function gets the msg to encrypt and the public key (exponent and n) of the server
	*/
	static std::string EncryptRSA(std::string msg, int e, int n);

};

