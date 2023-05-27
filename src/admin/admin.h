// admin.h


#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../user/User.h"

class DataBase; // Forward declaration of DataBase class

class Admin : public User {
private:
    string adminId;
    string adminName;
    std::string role = "admin"; // role fixed

    friend class DataBase;

public:
    Admin(std::string adminID, string userName, string userID, string userPW);
    std::string getFormattedData() const; // For database purposes
};

#endif
