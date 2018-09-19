#ifndef USER_H
#define USER_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class user
{
public:
    user(string userNameIn);
	std::string getUsername();
private:
	std::string username;

};
#endif
