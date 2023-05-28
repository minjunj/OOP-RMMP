#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../user/User.h"

class DataBase; // Forward declaration of DataBase class

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
    
    friend class DataBase;

public:
    Student(std::string stuId, int code, const std::string& userName, const std::string& userID, const std::string& userPW,  
             const std::string& class_, const std::string& room, 
            const bool gender, const std::string& mateID);


    std::string getFormattedData() const; // For database purposes
};

#endif