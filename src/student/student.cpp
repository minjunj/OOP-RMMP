#include "student.h"

Student::Student(std::string stuId, int code, std::string userName, std::string userID, std::string userPW,  
             const std::string& class_, int room, 
            char gender, int mateID): User(userID, userPW, userName), studentId(stuId),
            studentCode(code),  Gender(gender), roommateID(mateID), classOf(class_), roomId(room)
{
}

std::string Student::getFormattedData() const {
    return studentId + "," + std::to_string(studentCode) + "," + userName + "," + userID + ","
        + userPW + "," + classOf + "," + role + "," + std::to_string(roomId);
}