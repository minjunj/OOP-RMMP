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
	void testfunc();
	/*
	이 함수는 userType("student", "admin"), userId, userPw를 받아 데이터 베이스에 특정 정보를 가지고 있는
	유저가 있는지 확인해서 True, False를 리턴하는 함수다.
	*/

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