// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
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
    void insert(const std::vector<std::unique_ptr<T>>& data, const char* type); // Use std::shared_ptr

    /*
    string FindOne(string val, int val, int index)
    
    {학번,성명,ID,PW,학번앞쪽,닉네임,방ID}
    */
    std::string findOne(const char* type, std::string val, int index);

    std::string findAll(const char* type, std::string val);


    /*
        std::vector<std::unique_ptr<Student>> student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int roomId)
        스튜던트 데이터 입력하는 함수
    */
    std::vector<std::unique_ptr<Student>> student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int room);

    /* 어드민 데이터 입력하는 함수*/
    std::vector<std::unique_ptr<Admin>> admin_JSON(const std::string& name, const std::string& id, const std::string& pw);
    /* 룸 데이터 입력하는 함수*/
    std::vector<std::unique_ptr<Room>> room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty);
};

#endif
