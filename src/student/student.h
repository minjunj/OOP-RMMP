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
*/
class Student : public User{
private:
    int studentCode;
    char Gender;
    int roommateID;
    std::string studentName;
    std::string ID;
    std::string PW;
    std::string classOf;
    std::string role = "user"; // role 고정
    int roomId;

    friend class DataBase;

public:
    Student(string userID, string userPW, string userName, 
            int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int room) : User(userID, userPW, userName);

    

    std::string getFormattedData() const; // DB용


};

#endif
