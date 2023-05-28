// admin.cpp

#include "admin.h"


Admin::Admin(std::string adminID, string userName, string userID, string userPW)
    : User(userID, userPW, userName), adminId(adminId)

{
}

std::string Admin::getFormattedData() const {

    return adminId + "," + userName + "," + userID + "," + userPW + "," + role;

}

