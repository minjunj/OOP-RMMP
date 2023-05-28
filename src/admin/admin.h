// admin.h


#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../user/User.h"

class DataBase; // Forward declaration of DataBase class

/*
string userID; // user 상속
string userPW; // user 상속
string userName; // user 상속
string role = "admin" //fixed

[1] adminId : auto increased
[2] userName
[3] userId
[4] userPw
[5] role
*/
class Admin : public User {
private:


    std::string role = "admin"; // role fixed


    friend class DataBase;

public:

    Admin( const std::string& userName, const std::string& userID, const std::string& userPW);
    std::string getFormattedData() const; // For database purposes

};

#endif
