#pragma once
#include <string.h>
#include "User.h"



class AdminUser :
    public User
{
public:
    void printInfo();
    void changePW(string PW);
    void addStudent();
    void checkDorm();
    void clearDorm();
    void matchStudents();
};

