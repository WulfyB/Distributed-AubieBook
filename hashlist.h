#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include "user.h"
#include <fstream>
using namespace std;
class hashlist
{
private:
	string hashtag; //stores hashtag
public:
	string addHash(string activeUser, string temp)
	{
		if (!isFollowing(activeUser, temp)) {
			ofstream ofs(activeUser + "hash.txt", ofstream::app);
			ofs << temp + "\n";
			return "You are now following " + temp + "!";
		}
		return "You are already following " + temp + ".";

	}

	bool isFollowing(string activeUser, string temp)
	{
		ifstream ifs(activeUser + "hash.txt", ifstream::in);
		while (getline(ifs, hashtag))
		{
			if (temp == hashtag)
			{
				return true;
			}
		}
		return false;
	}
};