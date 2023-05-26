// main.cpp

#include <iostream>
#include <string>
#include "./user/User.h"
#include "./database/DataBase.h"
#include "./student/student.h"
#include "./admin/admin.h"
#include "./room/room.h"

using namespace std;
using JsonStu = std::vector<std::unique_ptr<Student>>;
using JsonAdmin = std::vector<std::unique_ptr<Admin>>;
using JsonRoom = std::vector<std::unique_ptr<Room>>;
void Login(string fileName)
{

    return;

}



void AdminLogin()
{


    return;
}

void UserLogin()
{


    return;
}

void start_menu()
{
    int st_num;

    cout << "+------------------------------------------+" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|         Roommate Matching System         |" << endl;
    cout << "|              Made by Seiun               |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            Enter the bellow              |" << endl;
    cout << "|               to Login                   |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            1. Admin Login                |" << endl;
    cout << "|            2. User  Login                |" << endl;
    cout << "|            3. Exit                       |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "+------------------------------------------+" << endl;

    while (1)
    {
        cout << "Enter the number here (1~3) : ";
        cin >> st_num;
        if (st_num != 1 and st_num != 2 and st_num != 3)
        {
            cout << "Wrong input, try again" << endl;
            continue;
        }
        else
        {
            if (st_num == 1)
            {
                AdminLogin();
            }
            else if (st_num == 2)
            {
                UserLogin();
            }
            else if (st_num == 3)
            {
                cout << "Ending program" << endl;
                return;
            }
        }
    }
    

}



int main()
{
    DataBase db;

    // JsonStu studentData = db.student_JSON(20225180, "조민준", "m412", "pw12", "22", 12); // 데이터 셋팅
    // JsonAdmin adminData = db.admin_JSON("조민준", "mw412", "pww12");
    // JsonRoom roomData = db.room_JSON("g107", true);
    // db.insert(studentData, "student"); //db에 삽입
    // db.insert(adminData, "admin");
    // db.insert(roomData, "room");

    // JsonStu studentData1 = db.student_JSON(20225180, "조민준1", "m4121", "pw121", "221", 121); // 데이터 셋팅
    // JsonAdmin adminData1 = db.admin_JSON("조민준1", "mw4121", "pww121");
    // JsonRoom roomData1 = db.room_JSON("g1071", true);
    // db.insert(studentData1, "student"); //db에 삽입
    // db.insert(adminData1, "admin");
    // db.insert(roomData1, "room");

    // JsonStu studentData2 = db.student_JSON(); // 데이터 셋팅
    // JsonAdmin adminData2 = db.admin_JSON();
    // JsonRoom roomData2 = db.room_JSON();
    // db.insert(studentData2, "student"); //db에 삽입
    // db.insert(adminData2, "admin");
    // db.insert(roomData2, "room");

    std::cout << db.findOne("student", "m4121", 21) << std::endl;

    // std::cout << db.findAll("student", "조민준1") << std::endl;

    // std::cout << db.findAll("room", "g1071") << std::endl;
    
    // std::cout << db.findAll("admin", "mw4121") << std::endl;

    // db.update("student", "2s", "content", 3);
    
    // db.inputData(2);
    // db.printData(2);
    // //db.outputData(5,"1234");
    // start_menu();    

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
