#include "RSAencryption.h"
#include <iostream>
#include <math.h> 

std::string RSAencryption::EncryptRSA(std::string msg, int e, int n)
{
    std::string encrypted = "";
    for (int i = 0; i < msg.length(); i++)
    {
        int value = int(msg[i]);
        int letterPOw = int(pow(value, e));
        
        int letter = letterPOw % n;
        encrypted += (letter + '0');
    }
    std::cout << "encrypted: " << encrypted << std::endl;

    return encrypted;
}
