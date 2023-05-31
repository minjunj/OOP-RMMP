// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include "../user/User.h"
using namespace std;

class User;
class Student;
class Admin;
class Room;

class DataBase {
private:
    std::string stuFile = "DB/student.txt";
    std::string adminFile = "DB/admin.txt";
    std::string roomFile = "DB/room.txt";
public:
    std::string findDB(const string type);

    /*
        데이터 베이스에 삽입하는 함수
        insert( _JSON으로 저장한 data, 저장위치 : admin, student, room)
    */
    template <typename T>
    void insert(const std::vector<std::unique_ptr<T>>& data, const string type); // Use std::shared_ptr

    /*
    To find one value you want.

    Database Index Info
    (Every Value Is Return Type String)

    -student
    [1] studentId : auto increased
    [2] studentCode
    [3] userName
    [4] userId
    [5] userPw
    [6] userClass
    [7] gender
    [8] role
    [9] roomId
    [10] classMateId

    -admin
    [1] adminId : auto increased
    [2] userName
    [3] userId
    [4] userPw
    [5] role

    -room
    [1] roomID : auto increased
    [2] roomNumber,
    [3] is_empty
    */
    std::string findOne(const std::string type, std::string val, int index);

    /*
    To find row you want.

    Database Index Info
    (Every Value Is Return Type String)

    -student
    [1] studentId : auto increased
    [2] studentCode
    [3] userName
    [4] userId
    [5] userPw
    [6] userClass
    [7] gender
    [8] role
    [9] roomId
    [10] classMateId

    -admin
    [1] adminId : auto increased
    [2] userName
    [3] userId
    [4] userPw
    [5] role

    -room
    [1] roomID : auto increased
    [2] roomNumber,
    [3] is_empty
    */
    std::string findAll(const std::string type, std::string val);

    /*
    To Update value you want.

    Database Index Info
    (Every Value Is Return Type String)

    -student
    [1] studentId : auto increased
    [2] studentCode
    [3] userName
    [4] userId
    [5] userPw
    [6] userClass
    [7] gender
    [8] role
    [9] roomId
    [10] classMateId

    -admin
    [1] adminId : auto increased
    [2] userName
    [3] userId
    [4] userPw
    [5] role

    -room
    [1] roomID : auto increased
    [2] roomNumber,
    [3] is_empty
    */
    void update(const std::string type, std::string primaryKey, std::string content, int index);


    //std::make_unique<Student>(studentId, code, name, id, pw, class_, room)

    /*
        std::vector<std::unique_ptr<Student>> student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
            const std::string& class_, int roomId)
        스튜던트 데이터 입력하는 함수
    */
    std::vector<std::unique_ptr<Student>> student_JSON(int code = 0, const std::string& name = "NULL", const std::string& id = "NULL", const std::string& pw = "NULL",
            const std::string& class_ = "NULL", const std::string& room = "NULL", const bool gender = true, const std::string& mateID = "NULL"); // 성별 기본 값은 ture


    // Admin(std::string adminID, string userName, string userID, string userPW);
    /* 어드민 데이터 입력하는 함수*/
    std::vector<std::unique_ptr<Admin>> admin_JSON(const std::string& name = "NULL", const std::string& id = "NULL", const std::string& pw = "NULL");



    bool findUser(const string userType, const string userId, const string userPw);
    unique_ptr<User> getUser(const string userType, const string userId, const string userPw);
    vector<string> getLineFromId(const string userType, const string userId);

    std::vector<std::unique_ptr<Room>> room_JSON(const std::string& roomNumber = "NULL", const bool is_empty = true, const bool status = true);


    
};
#endif
