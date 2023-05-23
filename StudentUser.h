#ifndef STUDENTUSER_H
#define STUDENTUSER_H
#include "./user/User.h"
#include "StudentInfo.h"
#include <string>


/*








Student로 통합합시다. 공사중









*/
class StudentUser :
    public User
{
private:
    int studentID;
    string dormID;
    char Gender;
    int roommate;

    StudentInfo stuInfo;

public:
    void printInfo();
    void changePW(string);
    bool hasRoommate();
    int findRoommate();
    void registerRoommate(int mateID);
    
    int getStudentID();
    string getDormID();
    char getGender();
    int getRoommate();

    void setStudentID(int sID);
    void setDormID(string dID);
    void setGender(char g);
    void setRoommate(int rID);

};

#endif