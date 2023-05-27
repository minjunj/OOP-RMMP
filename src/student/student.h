// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataBase; // Forward declaration of DataBase class

/*
    int : studentCode,
    string : studentName,
    string : ID,
    string : PW,
    string : classOf,
    string : role = "user"
    int : roomId
*/
class Student : public User{
private:
    std::string studentId;
    int studentCode;
    char Gender;
    int roomId;
    int roommateID;
    std::string classOf;
    std::string role = "user"; // role 고정
    

    friend class DataBase;

public:
    Student(string userID, string userPW, string userName, 
            int code, const std::string& class_, int room, 
            char gender, int mateID) : User(userID, userPW, userName);

    

    std::string getFormattedData() const; // DB용


};

#endif
