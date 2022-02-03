#pragma once
#include <string>

class RSAencryption
{
public:
	/*
	* The function gets a message and the elements that create the public key and encrypts the message with this key.
	* input: The message to encrypt and the public key.
	* output: The enccrypted message.
	*/
	static std::string EncryptRSA(std::string msg, int e, int n);

};

