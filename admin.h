// admin.h

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataBase; // Forward declaration of DataBase class

class Admin {
private:
    std::string adminName;
    std::string ID;
    std::string PW;
    std::string role = "admin"; // role 고정

    friend class DataBase;

public:
    Admin(const std::string& name, const std::string& id, const std::string& pw);

    std::string getFormattedData() const; // DB용
};

#endif
