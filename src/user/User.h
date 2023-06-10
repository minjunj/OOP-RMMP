#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include <memory>
#include "../database/DataBase.h"

using namespace std;

class DataBase;

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
	void testfunc();
	/*
	?΄ ?¨?? userType("student", "admin"), userId, userPwλ₯? λ°μ ?°?΄?° λ² μ΄?€? ?Ή?  ? λ³΄λ?? κ°?μ§?κ³? ??
	? ???κ°? ??μ§? ??Έ?΄? True, Falseλ₯? λ¦¬ν΄?? ?¨??€.
	*/

	virtual string getFormattedData() const =0;

	virtual void registerRoommate(DataBase db) = 0;
	virtual void findRoommate(DataBase db) = 0;
	virtual void releaseRoommate(DataBase db) = 0;
	virtual void registerRoom(DataBase db) = 0;
	virtual void releaseRoom(DataBase db) = 0;
	virtual void insertInfo(DataBase db) = 0;

	virtual void addDelStudents(DataBase db) = 0;
	virtual void addDelRoom(DataBase db) = 0;
	virtual void matchRoommates(DataBase db) = 0;
	virtual void cleanRoom(DataBase db) = 0;
	virtual void logout() = 0;

	virtual void printInfo() = 0;

	virtual bool isInfo() = 0;
	virtual void checkRoom(DataBase db) = 0;
	virtual void checkStudents(DataBase db) = 0;


	virtual string getUserName() = 0;
};

#endif