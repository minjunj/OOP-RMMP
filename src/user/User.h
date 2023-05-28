#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

using namespace std;

class User {
protected:
	string userID;
	string userPW;
	string userName;

public:
	User(string ID, string PW, string Name);

	string getuserID();
	string getuserPW();
	string getuserName();
	void setuserID(string ID);
	void setuserPW(string PW);
	void setuserName(string Name);


	void doLogout();
	void changePW();

	virtual string getFormattedData();

	virtual void registerRoommate();
    virtual void findRoommate();
    virtual void registerRoom();
    virtual void insertInfo();

	virtual void checkRoom();
    virtual void addDelStudents();
    virtual void addDelRoom();
    virtual void matchRoommates();
    virtual void cleanRoom();
    virtual void logout();

};

#endif