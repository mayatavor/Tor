#include "RSAencryption.h"
#include <iostream>
#include <math.h> 
#include <sstream>
#include <locale>

unsigned long int p(int x, int y) {
    unsigned long int res = 1;
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return res;
}

std::string RSAencryption::EncryptRSA(std::string msg, int e, int n)
{
    std::string encrypted = "";
    for (int i = 0; i < msg.length(); i++)
    {
        int value = int(msg[i]);
        //int value = 2;
        std::cout << "val " << value << std::endl;

        //long int letterPOw = long int(pow(value, e));
        //unsigned long int letterPOw = p(value, e);
        
        //int letter = (p(value, e)) % n;
        double letter = pow(value, e);
        letter = fmod(letter, n);

        std::cout << "letter " << letter << std::endl;
        encrypted += (letter);
    }
    std::cout << "encrypted: " << encrypted << std::endl;

    return encrypted;
}

std::vector<int> RSAencryption::EncryptRSA1(std::string msg, int e, int n, std::vector<int>& encrypted)
{
    for (int i = 0; i < encrypted.size(); i++)
    {
        int value = encrypted[i];

        std::cout << "val " << value << std::endl;

        double letter = pow(value, e);
        letter = fmod(letter, n);

        std::cout << "letter " << letter << std::endl;
        encrypted[i] = letter;
    }
    for (int i = 0; i < msg.length(); i++)
    {
        int value = int(msg[i]);
        
        std::cout << "val " << value << std::endl;

        double letter = pow(value, e);
        letter = fmod(letter, n);

        std::cout << "letter " << letter << std::endl;
        encrypted.push_back(letter);
    }
    //std::cout << "encrypted: " << encrypted << std::endl;

    return encrypted;
}

std::string RSAencryption::EncryptRSA2(std::string msg, int e, int n)
{
    std::string encrypted = "";
    for (int i = 0; i < msg.size(); i++)
    {
        int value = msg[i];

        std::cout << "val " << value << std::endl;

        double letter = pow(value, e);
        letter = fmod(letter, n);

        std::cout << "letter " << letter << std::endl;
        msg[i] = letter;
    }
    for (int i = 0; i < msg.size(); i++)
    {
        int value = int(msg[i]);

        std::cout << "val " << value << std::endl;

        double letter = pow(value, e);
        letter = fmod(letter, n);

        std::cout << "letter " << letter << std::endl;
        encrypted.push_back(letter);
        encrypted.push_back('~');
    }

    return encrypted;
}
