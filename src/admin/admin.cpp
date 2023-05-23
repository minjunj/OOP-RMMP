// admin.cpp

#include "admin.h"

Admin::Admin(const std::string& name, const std::string& id, const std::string& pw)
    : adminName(name), ID(id), PW(pw)
{
}

std::string Admin::getFormattedData() const {
    return adminName + "," + ID + "," + PW + "," + role;
}
