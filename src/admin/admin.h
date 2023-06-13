// admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "../user/User.h"
//#include "../database/DataBase.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

class DataBase; // Forward declaration of DataBase class


/*
string userID; // user Inherit 
string userPW; // user Inherit 
string userName; // user Inherit 
string role = "admin" //fixed

[1] adminId : auto increased
[2] userName
[3] userId
[4] userPw
[5] role
[6] isLogin
*/
class Admin : public User {
private:

    std::string adminId;
    std::string role = "admin"; // role fixed


    friend class DataBase;

public:

    Admin( std::string adminId, const std::string& userName, const std::string& userID, const std::string& userPW);
    std::string getFormattedData() const override; // For database purposes

    void addDelStudents(DataBase db) ;
    void addDelRoom(DataBase db) ;
    void matchRoommates(DataBase db) ;
    void cleanRoom(DataBase db) ;


    void checkRoom(DataBase db) ;
    void checkStudents(DataBase db) ;



    void releaseRoom(DataBase db) ;
    void releaseRoommate(DataBase db) ;
	void registerRoommate(DataBase db);
    void findRoommate(DataBase db);
    void registerRoom(DataBase db);
    void insertInfo(DataBase db);
	void printInfo();
    string getsurveyId();
	string getUserName();
};

#endif
