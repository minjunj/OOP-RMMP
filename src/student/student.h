#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../user/User.h"

class DataBase; // Forward declaration of DataBase class

/*
	string userID; //user 상속
	string userPW;
	string userName;
    std::string studentId; //auto increased
    int studentCode;
    char Gender;
    int roomId;
    int roommateID;
    std::string classOf;
    std::string role = "user"; // role fixed
*/
class Student : public User {

private:
    std::string studentId; //auto increased
    int studentCode;
    char Gender;
    std::string roomId;
    int roommateID;
    std::string classOf;
    std::string role = "user"; // role fixed
    
    friend class DataBase;

public:
    Student(std::string stuId, int code, std::string userName, std::string userID, std::string userPW,  
             const std::string& class_, std::string room, 
            char gender, int mateID);


    std::string getFormattedData() const; // For database purposes
};

#endif