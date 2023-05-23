#include <string.h>
#include "User.h"
#ifndef ADMIN_H
#define ADMIN_H

/*








admin 통합합시다. 공사중









*/
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

#endif