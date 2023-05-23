// student.cpp
#include "student.h"

Student::Student(int code, const std::string& name, const std::string& id, const std::string& pw,
                 const std::string& class_, int room)
    : studentCode(code), studentName(name), ID(id), PW(pw), classOf(class_), roomId(room)
{
}

std::string Student::getFormattedData() const {
    return std::to_string(studentCode) + "," + studentName + "," + ID + ","
        + PW + "," + classOf + "," + role + "," + std::to_string(roomId);
}