// DataBase.h
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"

class Student;
class Admin;
class Room;

class DataBase {
private:
    std::string stuFile = "student.txt";
    std::string adminFile = "admin.txt";
    std::string roomFile = "room.txt";
public:
    /*
        데이터 베이스에 삽입하는 함수
        insert( _JSON으로 저장한 data, 저장위치 : admin, student, room)
    */
    template <typename T>
    void insert(const std::vector<T>& data, const char* type); // type은 student, admin 등

    /*
        std::vector<Student> student_JSON(int code, string name, string id, string pw, string classOf, int roomID)
        스튜던트 데이터 입력하는 함수
    */
    std::vector<Student> student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int room);

    /* 어드민 데이터 입력하는 함수*/
    std::vector<Admin> admin_JSON(const std::string& name, const std::string& id, const std::string& pw);
    /* 룸 데이터 입력하는 함수*/
    std::vector<Room> room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty);
};

#endif


