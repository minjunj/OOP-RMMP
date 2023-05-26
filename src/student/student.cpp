// student.cpp
#include "student.h"

Student::Student(const std::string& studentId, int code, const std::string& name, const std::string& id, const std::string& pw,
                 const std::string& class_, int room)
    : studentId(studentId), studentCode(code), studentName(name), ID(id), PW(pw), classOf(class_), roomId(room)
{
}

std::string Student::getFormattedData() const {
    return studentId + "," + std::to_string(studentCode) + "," + studentName + "," + ID + ","
        + PW + "," + classOf + "," + role + "," + std::to_string(roomId);
}