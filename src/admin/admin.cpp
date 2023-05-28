// admin.cpp

#include "admin.h"
int count_admin = 0;

Admin::Admin( std::string userName, std::string userID, std::string userPW)
    : User(userID, userPW, userName)

{
}

std::string Admin::getFormattedData() const {

    count_admin++;
    std::string a = "a";
    std::string adminId = std::to_string(count_admin) + a;
    return  adminId + "," + userName + "," + userID + "," + userPW + "," + role;

}

