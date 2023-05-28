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
string adminId
string role = "admin" //fixed
*/
class Admin : public User {
private:

    //std::string adminId;
    std::string role = "admin"; // role fixed


    friend class DataBase;

public:

    Admin( string userName, string userID, string userPW);
    std::string getFormattedData() const; // For database purposes

};

#endif
