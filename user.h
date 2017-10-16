#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include "friendlist.h"
#include <fstream>
using namespace std;

class user
{
private:
	string username; //stroes username for class functions

public:
	void addUserList(string temp) //adds new user to list
	{
		ofstream ofs("userlist.txt", ofstream::app);
		ofs << temp + "\n";


	}
	bool checkUserList(string temp) //checks if user exists in list
	{
		ifstream ifs("userlist.txt", ifstream::in);
		while (getline(ifs, username))
		{
			if (temp == username)
			{
				return true;
			}
		}
		return false;
	}



};

