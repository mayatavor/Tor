#pragma once
#include <string>
#include <vector>

class RSAencryption
{
public:
	/*
	* The function gets a message and the elements that create the public key and encrypts the message with this key.
	* input: The message to encrypt and the public key.
	* output: The enccrypted message.
	*/
	static std::string EncryptRSA(std::string msg, int e, int n);

	static std::vector<int> EncryptRSA1(std::string msg, int e, int n, std::vector<int>& vec);

	static std::string EncryptRSA2(std::string msg, int e, int n);
};

