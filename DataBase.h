// DataBase.h
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Student;
class Admin;
class Room;

class DataBase {
private:
    std::string stuFile = "student.txt";
    std::string adminFile = "admin.txt";
    std::string roomFile = "room.txt";
public:
    template <typename T>
    void insert(const std::vector<T>& data, const char* type); // type은 student, admin 등

    /*std::vector<Student> student_JSON(int code, string name, string id, string pw, string classOf, int roomID)*/
    std::vector<Student> student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int room);

    /**/
    std::vector<Admin> admin_JSON(const std::string& name, const std::string& id, const std::string& pw);

    std::vector<Room> room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty);
};

#endif


