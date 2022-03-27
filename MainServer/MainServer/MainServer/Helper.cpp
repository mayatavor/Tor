#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	return atoi(s);
}

// recieve data from socket according byteSize
// returns the data as string
std::string Helper::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	std::string res(s);
	return res;
}

// return std::string after padding zeros if necessary
std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

// recieve data from socket according byteSize
// this is private function
char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// send data to socket
// this is private function
void Helper::sendData(SOCKET sc, std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

void Helper::sendData(SOCKET sc, std::vector<int> msg)
{
	/*if (send(sc, msg.data(), msg.size() * sizeof(msg[0]), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}*/
	
	send(sc, (char*)(msg.data()), msg.size() * sizeof(int), 0);
}


