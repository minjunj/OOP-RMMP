// admin.cpp

#include "admin.h"
int count_admin = 0;

Admin::Admin( const std::string& userName, const std::string& userID, const std::string& userPW)
    : User(userID, userPW, userName)

{
}

std::string Admin::getFormattedData() const {


    count_admin++;
    std::string a = "a";
    std::string adminId = std::to_string(count_admin) + a;
    return  adminId + "," + userName + "," + userID + "," + userPW + "," + role;


}

void checkRoom()
{

    return;
}
void addDelStudents()
{

    return;
}
void addDelRoom()
{
    return;
}
void matchRoommates()
{


    return;
}
void cleanRoom()
{
    return;
}
void logout()
{
    return;
}