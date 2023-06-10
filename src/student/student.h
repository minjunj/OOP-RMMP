#ifndef STUDENT_H
#define STUDENT_H

#include "../user/User.h"
#include "../database/DataBase.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <memory>


using namespace std;
class DataBase; // Forward declaration of DataBase class
class User;
/*
	[1] studentId : auto increased
    [2] studentCode
	[3] userName
	[4] userId
    [5] userPw
    [6] userClass
    [7] gender
    [8] role
    [9] roomId
    [10] classMateId
*/
class Student : public User {

private:
    std::string studentId; //auto increased
    int studentCode;
    bool gender;
    std::string roomId;
    std::string roommateID;
    std::string classOf;
    std::string role = "user"; // role fixed
    std::string surveyId;
    
    friend class DataBase;

public:
    Student(std::string stuId, int code, const std::string& userName, const std::string& userID, const std::string& userPW,  
             const std::string& class_, const std::string& room, 
            const bool gender, const std::string& mateID, const std::string& surveyId);

    //~Student();
    std::string getFormattedData() const; // For database purposes
    void registerRoommate(DataBase db) ;
    void findRoommate(DataBase db) ;
    void registerRoom(DataBase db) ;
    void insertInfo(DataBase db) ;
    void releaseRoommate(DataBase db) ;
    bool isInfo() ;
    void releaseRoom(DataBase db) ;
    string getUserName();
    void checkRoom(DataBase db) ;

    string getsurveyId();

    void addDelStudents(DataBase db);
    void addDelRoom(DataBase db);
    void matchRoommates(DataBase db);
    void cleanRoom(DataBase db);
	void printInfo();
	void checkStudents(DataBase db);


};

#endif