// admin.cpp

#include "admin.h"

Admin::Admin(const std::string& adminId, const std::string& name, const std::string& id, const std::string& pw)
    : adminId(adminId), adminName(name), ID(id), PW(pw)
{
}

std::string Admin::getFormattedData() const {
    return adminId + "," + adminName + "," + ID + "," + PW + "," + role;
}
