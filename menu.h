#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include "hashlist.h"
#include "user.h"
#include "friendlist.h"
#include <time.h>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

class menu {
private:
	string menuOptions = "Menu options can be chosen by entering the relevant key: New user (n), log-in/Log-out (l), Post (p),\n Wall page (w), Home page (h), Manage friends (m), Follow hashtag (f), Quit (q).\n";


public:
	int aubieBook()
	{
		string endLoop = "a"; //Keeps loop going
		string userSInput; //Stores current string input
		char userCInput; //Stores current char input
		string banner = "Welcome to the Distrubatable AubieBook!"; //Holds display banner for outputs
		string temp; //stores temporary string inputs
		string temp2; //stores temporary data
		user user; //instance of user 
		friendlist friendlist; //instance of friendlist 
		hashlist hashlist; //instance of hashlist 
		string activeUser; //current user
		size_t alphaCheck; //Used to check illegal input characters
		size_t spaces; //tracks excess space after banner is added to output messages
		bool online = false;  //verifies online status of active user
		size_t count; //tracks counts for loops
		time_t timer; //tracks time


		spaces = 56 - banner.length();
		cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
			<< "===================================================\n"
			<< string(12, ' ')
			<< "\n"
			<< string(12, ' ')
			<< "|"
			<< string(spaces / 2, ' ')
			<< banner
			<< string(spaces - spaces / 2, ' ')
			<< "|"
			<< string(12, ' ')
			<< "\n"
			<< string(12, ' ')
			<< "===================================================\n"
			<< string(12, ' ')
			<< "\n"
			<< "\n";
		while (endLoop != "end")
		{

			cout << "\n=====================================================================================================\n"
				<< menuOptions
				<< "\nEnter selection:\n";
			temp.clear();
			while (temp.empty())
			{
				getline(cin, temp);
			}
			userCInput = temp.at(0);
			userCInput = tolower(userCInput);
			switch (userCInput)
			{
			case'n':
				if (online)
				{
					cout << "To create a new user, you must not be logged in. Please log out first.\n";
				}
				else
				{
					cout << "Please input a unique username. Please only use alphanumeric characters. Usernames must contain a letter.\n";


					getline(cin, temp);// create new user
					alphaCheck = temp.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
					if (alphaCheck != string::npos)
					{
						cout << "Usernames must be alphanumerical only.\n";
						break;
					}//check for illegal characters.
					alphaCheck = temp.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
					if (alphaCheck == string::npos)
					{
						cout << "Usernames must contain at least one letter.\n";
						break;
					}
					if (!user.checkUserList(temp))
					{
						user.addUserList(temp);
						activeUser = temp;
						temp = "";
						online = true;
						banner = "Welcome to Aubiebook, " + activeUser + "!";
						spaces = 56 - banner.length();

						cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
							<< "===========================================================\n"
							<< string(12, ' ')
							<< "\n"
							<< string(12, ' ')
							<< "|"
							<< string(spaces / 2, ' ')
							<< banner
							<< string(spaces - spaces / 2, ' ')
							<< "|"
							<< string(12, ' ')
							<< "\n\n"
							<< string(12, ' ')
							<< "===========================================================\n"
							<< string(12, ' ')
							<< "\n";
					}
					else
					{
						cout << "Another user already has that name. Please choose a unique username, or log in!";
					}
				}
				break;
			case 'l':
				if (online)
				{
					cout << "You are logged in as " + activeUser + ". Do you wish to log out? (y/n)\n";
					userCInput = 'x';
					while (userCInput != 'y' && userCInput != 'n')
					{
						temp.clear();
						while (temp.empty())
						{
							getline(cin, temp);
						}
						userCInput = temp.at(0);
						userCInput = tolower(userCInput);
						if (userCInput != 'y' && userCInput != 'n')
						{
							cout << "Please enter y to log out or n to stay logged in.\n";
						}
					}


					if (userCInput == 'y')
					{
						activeUser = "";
						online = false;
						cout << "You are now logged out!\n";
						break;
					}
					else if (userCInput == 'n')
					{
						cout << "Please choose a different menu option.\n";
						break;
					}

				}
				else
				{
					cout << "Please enter your username.\n";
					getline(cin, temp);
					alphaCheck = temp.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
					if (alphaCheck == string::npos)
					{
						cout << "Usernames must contain at least one letter.\n";
						break;
					}
					if (!user.checkUserList(temp))
					{
						cout << "User does not exist. Please create new user.\n";
						break;
					}
					else
					{
						activeUser = temp;
						online = true;
						banner = "Welcome back to AubieBook " + activeUser;
						cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
							<< "===========================================================\n"
							<< string(12, ' ')
							<< "\n"
							<< string(12, ' ')
							<< "|"
							<< string(spaces / 2, ' ')
							<< banner
							<< string(spaces - spaces / 2, ' ')
							<< "|"
							<< string(12, ' ')
							<< "\n\n"
							<< string(12, ' ')
							<< "===========================================================\n"
							<< string(12, ' ')
							<< "\n";
						break;
					}
					break;
				}
			case 'p':
				if (online)
				{
					cout << "Enter new post. To terminate, type $$ as a line input.\n";
					string userPost; //stores user next post line.
					string tempBuffer; //Holds actively formed user post
					while (userPost != "$$")
					{
						size_t secureCheck; //Prevents using illegal char combinations
						getline(cin, userPost);
						secureCheck = userPost.find("%[");
						if (secureCheck == string::npos)
						{
							secureCheck = userPost.find("]%");
							if (secureCheck == string::npos)
							{
								if (userPost != "$$")
								{
									tempBuffer += userPost + "$^";
								}
							}
							else
							{
								cout << "Previous line was not saved due to illegal character combination.\n";
							}
						}
						else
						{
							cout << "Previous line was not saved due to illegal character combination.\n";
						}
					}
					ofstream ofs(activeUser + ".txt", ofstream::app);
					timer = time(nullptr);
					auto tm = localtime(&timer);
					ofs << "%[" << setw(2) << setfill('0') << tm->tm_year % 100;
					ofs << setw(2) << setfill('0') << tm->tm_mon;
					ofs << setw(2) << setfill('0') << tm->tm_mday;
					ofs << setw(2) << setfill('0') << tm->tm_hour;
					ofs << setw(2) << setfill('0') << tm->tm_min;
					ofs << setw(2) << setfill('0') << tm->tm_sec << "]%";
					ofs << tempBuffer + "\n";

				}
				else
				{
					cout << "Please login before posting! \n";
				}
				break;
			case 'w':
				if (online)
				{
					banner = activeUser + "'s Wall Page";
					spaces = 56 - banner.length();
					cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
						<< "===========================================================\n"
						<< string(12, ' ')
						<< "\n"
						<< string(12, ' ')
						<< "|"
						<< string(spaces / 2, ' ')
						<< banner
						<< string(spaces - spaces / 2, ' ')
						<< "|"
						<< string(12, ' ')
						<< "\n"
						<< string(12, ' ')
						<< "===========================================================\n"
						<< string(12, ' ')
						<< "\n"
						<< "\n";
					ifstream ifs(activeUser + ".txt", ifstream::in);
					count = 0;
					temp2 = "x";
					size_t newLine;
					vector<string> wallPosts;
					while (getline(ifs, temp))
					{
						wallPosts.push_back(temp);
					}
					sort(wallPosts.begin(), wallPosts.end()); //sort vector by timestamp
					for (int i = wallPosts.size() - 1; i >= 0; i--)
					{
						if (count > 2 && temp2 == "x") //Displays 3, then checks if user would like to see older messages.
						{
							while (userCInput != 'y' && userCInput != 'n')
							{
								cout << "See more messages? Enter yes(y) or no(n).";
								temp2.clear();
								while (temp2.empty())
								{
									getline(cin, temp2);
								}
								userCInput = temp2.at(0);
								userCInput = tolower(userCInput);
								if (userCInput == 'n')
								{
									temp2 = "end";
								}
							}
						}
						if (temp2 == "end")
						{
							break;
						}
						temp = wallPosts[i];
						temp = temp.substr(16);
						while ((newLine = temp.find("$^")) != string::npos)
						{
							temp.replace(newLine, 2, "\n");
						}
						cout << temp + "\n\n";
						count++;
					}

				}
				else
				{
					cout << "In order to view wallpage, please first login!";
				}
				break;
			case 'h':
				if (online)
				{
					banner = activeUser + "'s Home Page";
					spaces = 56 - banner.length();
					cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
						<< "===========================================================\n"
						<< string(12, ' ')
						<< "\n"
						<< string(12, ' ')
						<< "|"
						<< string(spaces / 2, ' ')
						<< banner
						<< string(spaces - spaces / 2, ' ')
						<< "|"
						<< string(12, ' ')
						<< "\n"
						<< string(12, ' ')
						<< "===========================================================\n"
						<< string(12, ' ')
						<< "\n"
						<< "\n";
					ifstream userPosts(activeUser + ".txt", ifstream::in);
					size_t count = 0;
					size_t newLine;
					vector<string> homePosts;
					ifstream userList("userlist.txt", ifstream::in);
					string temp3; //Stores the time component
					while (getline(userList, temp))
					{
						ifstream tempPosts(temp + ".txt", ifstream::in);
						if (friendlist.isFriend(activeUser, temp) || temp == activeUser)
						{
							while (getline(tempPosts, temp2))
							{
								temp3 = temp2.substr(0, 16);
								temp2 = temp2.substr(16);
								temp2 = temp3 + temp + ">>\n\n" + temp2;
								homePosts.push_back(temp2);
							}
						}
						else
						{
							string hashtag;
							size_t hashloc;
							while (getline(tempPosts, temp2))
							{
								ifstream hash(activeUser + "hash.txt", ifstream::in);
								while (getline(hash, hashtag))
								{
									hashloc = temp2.find(hashtag);
									if (hashloc != string::npos)
									{
										temp3 = temp2.substr(0, 16);
										temp2 = temp2.substr(16);
										temp2 = temp3 + temp + ">>\n\n" + temp2;
										homePosts.push_back(temp2);
										break;
									}
								}
								hash.seekg(0);
								hash.clear();
							}
						}
					}
					sort(homePosts.begin(), homePosts.end());//sorts vector by timestap (standardized length of 16 characters.
					count = 0;
					temp2 = "x";
					for (int i = homePosts.size() - 1; i >= 0; i--)
					{
						if (count > 2 && temp2 == "x") //Displays 3, then checks if user would like to see older messages.
						{
							while (userCInput != 'y' && userCInput != 'n')
							{
								cout << "See more messages? Enter yes(y) or no(n).";
								temp2.clear();
								while (temp2.empty())
								{
									getline(cin, temp2);
								}
								userCInput = temp2.at(0);
								userCInput = tolower(userCInput);
								if (userCInput == 'n')
								{
									temp2 = "end";
									break;
								}
							}
						}
						if (temp2 == "end")
						{
							break;
						}
						temp = homePosts[i];
						temp = temp.substr(16);
						while ((newLine = temp.find("$^")) != string::npos)
						{
							temp.replace(newLine, 2, "\n");
						}
						cout << temp + "\n\n";
						count++;


					}
				}
				else
				{
					cout << "In order to view homepage, please first login!";
				}
				break;
			case 'm':
				if (online)
				{
					cout << "What is the username of the friend you wish to add? (To cancel, enter $$ as new line)";
					getline(cin, userSInput);
					if (userSInput != "$$")
					{
						cout << friendlist.addFriend(activeUser, userSInput);
					}
					else
					{
						cout << "Please select a different menu option.";
					}
				}
				else
				{
					cout << "In order to view wallpage, please first login!";
				}
				break;
			case 'f':
				if (online)
				{
					cout << "What is the #topic you wish to follow? \nRemember, hashtags can only use alphabetical characters and be preceeded by a #. "
						<< "(To cancel, enter $$)";
					getline(cin, userSInput);
					alphaCheck = userSInput.find_first_of("#");
					if (userSInput == "$$")
					{
						break;
					}
					if (alphaCheck != 0)
					{
						cout << "#topics must begin with a #.";
						break;
					}
					alphaCheck = userSInput.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 1);
					if (alphaCheck != string::npos)
					{
						cout << "#topics must ONLY contain alphabetical characters after the #.";
						break;
					}
					cout << hashlist.addHash(activeUser, userSInput);
				}
				else
				{
					cout << "In order to view wallpage, please first login!";
				}
				break;
			case 'q':
				endLoop = "end";// exit program
				banner = "Thank you for using AubieBook";
				spaces = 56 - banner.length();
				cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
					<< "===========================================================\n"
					<< string(12, ' ')
					<< "\n"
					<< string(12, ' ')
					<< "|"
					<< string(spaces / 2, ' ')
					<< banner
					<< string(spaces - spaces / 2, ' ')
					<< "|"
					<< string(12, ' ')
					<< "\n"
					<< string(12, ' ')
					<< "===========================================================\n"
					<< string(12, ' ')
					<< "\n"
					<< "\n";
				break;
			default: cout << "That input is not a valid. Please refer to menu options and try again.\n\n\n";
				break;
			}
		}

		return 0;
	}
};
