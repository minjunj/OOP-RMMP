#include "User.h"
#include <iostream>
#include <string>

using namespace std;


User::User(string ID="", string PW="", string Name="")
{
	cout << "User Constructed" << endl;
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

void User::testfunc()
{
	return;
}

void User::doLogout()
{
	cout << "Logging out from user?"<<endl;
	return;
}

void User::printInfo()
{
	cout << "User ID : " << userID << endl;
	cout << "User PW : " << userPW << endl;
	cout << "User Name : " << userName << endl;

}
void User::changePW()
{
	string checkPW;
	string newPW;
	string checkNewPW;
	unsigned int minlen = 7;

	cout << "Enter the original Password(To cancle enter 0): ";
	cin >> checkPW;

	while (checkPW != "0" and checkPW != userID)
	{
		cout << "Wrong Password try again(To cancle enter 0): ";
		cin >> checkPW;
	}

	if (checkPW == "0")
	{
		return;
	}
	else
	{
		cout << "Enter new Password(longer than 7 letters): ";
		cin >> newPW;
		cout << "Check new Password(To cancle enter 0): ";
		cin >> checkNewPW;

		if (newPW != checkNewPW or checkNewPW.length() > minlen)
		{
			if (newPW == "0")
			{
				return;
			}
			cout << "Check new Password again(To cancle enter 0): ";
			cin >> checkNewPW;
		}
	}

	setuserPW(newPW);
	cout << "\nPassword changed to " << getuserPW() << endl;

	return;
}







virtual string User::getFormattedData()
{
	cout<<"Error : Invalid move"<<endl;
}

virtual void User::registerRoommate()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::findRoommate()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::registerRoom()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::insertInfo()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::checkRoom()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::addDelStudents()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::addDelRoom()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::matchRoommates()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::cleanRoom()
{
	cout<<"Error : Invalid move"<<endl;
}
virtual void User::logout()
{
	cout<<"Error : Invalid move"<<endl;
}