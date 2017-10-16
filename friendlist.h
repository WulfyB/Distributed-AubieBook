#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include "user.h"
#include <fstream>
using namespace std;
class friendlist
{
private: 
	string username; //username of friends from file

public:
	string addFriend(string activeUser, string temp)
	{
		ifstream ifs("userlist.txt", ifstream::in);
		while (getline(ifs, username))
		{
			if (temp == username)
			{
				if (!isFriend(activeUser, temp)) {
					ofstream ofs(activeUser + "friends.txt", ofstream::app);
					ofs << temp + "\n";
					return temp + " is now your friend!";
				}
				else
				{
					return temp + " is already your friend!";
				}
			}
		}
		return "User not found. " + temp + " not added.";
	}

	bool isFriend(string activeUser, string temp)
	{
		ifstream ifs(activeUser + "friends.txt", ifstream::in);
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