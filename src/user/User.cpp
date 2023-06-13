#include "User.h"
#include <iostream>
#include <string>

using namespace std;


User::User(string ID="", string PW="", string Name="")
{
	//cout << "User Constructed" << endl;
	cout << endl;
	setuserID(ID);
	setuserPW(PW);
	setuserName(Name);
}
string User::getuserID()
{
	return userID;
}
string User::getuserPW()
{
	return userPW;
}
string User::getuserName()
{
	return userName;
}
void User::setuserID(string ID)
{
	userID = ID;
}
void User::setuserPW(string PW)
{
	userPW = PW;
}
void User::setuserName(string Name)
{
	userName = Name;
}
