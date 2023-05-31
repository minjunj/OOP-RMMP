// main.cpp

#include <iostream>
#include <string>
#include <memory>
#include "./user/User.h"
#include "./database/DataBase.h"
#include "./student/student.h"
#include "./admin/admin.h"
#include "./room/room.h"

using namespace std;
using JsonStu = std::vector<std::unique_ptr<Student>>;
using JsonAdmin = std::vector<std::unique_ptr<Admin>>;
using JsonRoom = std::vector<std::unique_ptr<Room>>;


unique_ptr<User> Login(DataBase db, string userType)
{
    string file;
    string userId, userPw;

    while(1)
    {
        cout << "Enter User ID : ";
        cin  >> userId;
        cout << "Enter the User Password : ";
        cin  >> userPw;
        
        if(db.findUser(userType, userId, userPw))
        {
            return db.getUser(userType, userId, userPw);
        }
        else
        {
            cout << "Wrong ID or password, try again" << endl;
        }
    }
}

void startMenuTemplate()
{
    cout << endl;
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
    return;
}
void studentMenuTemplate1()
{
    cout<< "hello"<<endl;
    cout << "+------------------------------------------+" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Student Menu                |" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Studnet Name:               |" << endl;
    cout << "|                  Name                    |" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Info : Okay                 |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            Enter the bellow              |" << endl;
    cout << "|               to Use                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            1. Register Roommate          |" << endl;
    cout << "|            2. Find Roommate              |" << endl;
    cout << "|            3. Check Rooms                |" << endl;
    cout << "|            4. Register Room              |" << endl;
    cout << "|            5. Check Info                 |" << endl;
    cout << "|            6. Change Info                |" << endl;
    cout << "|            7. Logout                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "+------------------------------------------+" << endl;
    return;
}
void studentMenuTemplate2()
{
    cout << "+------------------------------------------+" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Student Menu                |" << endl;
    cout << "|                                          |" << endl;
    cout << "|              Studnet Name:               |" << endl;
    cout << "|                  Name                    |" << endl;
    cout << "|                                          |" << endl;
    cout << "|              No User Info                |" << endl;
    cout << "|              Need to Enter               |" << endl;
    cout << "|              default Info                |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            Enter the bellow              |" << endl;
    cout << "|               to Use                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            1. Insert Info                |" << endl;
    cout << "|            2. Logout                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "+------------------------------------------+" << endl;
}

void adminMenuTemplate1()
{
    cout << "+------------------------------------------+" << endl;
    cout << "|                                          |" << endl;
    cout << "|            Administrator Menu            |" << endl;
    cout << "|                                          |" << endl;
    cout << "|               Admin Name:                |" << endl;
    cout << "|                  Name                    |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            Enter the bellow              |" << endl;
    cout << "|               to Use                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            1. Check Students             |" << endl;
    cout << "|            2. Check Rooms                |" << endl;
    cout << "|            3. Add/Del Students           |" << endl;
    cout << "|            4. Add/Del Rooms              |" << endl;
    cout << "|            5. Match Roommates            |" << endl;
    cout << "|            6. Clean Room                 |" << endl;
    cout << "|            7. Logout                     |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "+------------------------------------------+" << endl;
    return;
}




void studentMenu(unique_ptr<User>& student, DataBase db)
{
    if (student->isInfo())
    {
        int menuNum;
        while (1)
        {
            studentMenuTemplate1();
            cout << "Enter the Number to use : ";
            cin  >> menuNum;
            switch (menuNum)
            {
            case 1:
                student->registerRoommate(db);
                break;
            case 2:
                student->findRoommate(db);
                break;
            case 3:
                student->checkRoom(db); // DataBase에서 새로 들어줘야할 함수, 현재 기숙사의 전체적인 현황(비어있는지, 방에 몇명 있는지 등) 한 눈에 볼 수 있는 함수가 필요
                break;
            case 4:
                student->registerRoom(db);
                break;
            case 5:
                cout << student->getFormattedData() << endl;
                break;
            case 6:
                student->insertInfo(db);
                break;
            case 7:
                cout << "Logging out" << student->getUserName() << endl;
                student->logout();
                return;
            default:
                cout << "Wrong Input, please try again" << endl;
                break;
            }
        }
    }
    else
    {
        int menuNum;
        while (1)
        {
            studentMenuTemplate2();
            cout << "Enter the Number to use : ";
            cin  >> menuNum;
            switch (menuNum)
            {
            case 1:
                student->insertInfo(db);
                break;
            case 2:
                cout << "Logging out" << student->getUserName() << endl;
                student->logout();
                return;
            default:
                cout << "Wrong Input, please try again" << endl;
                break;
            }
        }
    }
    return;
}


void adminMenu(unique_ptr<User>& admin, DataBase db)
{
    int menuNum;
    while (1)
    {
        adminMenuTemplate1();
        cout << "Enter the Number to use : ";
        cin  >> menuNum;
        switch (menuNum)
        {
        case 1:
            admin->checkStudents(db);
            break;
        case 2:
            admin->checkRoom(db);
            break;
        case 3:
            admin->addDelStudents(db); // DataBase에서 새로 들어줘야할 함수, 현재 기숙사의 전체적인 현황(비어있는지, 방에 몇명 있는지 등) 한 눈에 볼 수 있는 함수가 필요
            break;
        case 4:
            admin->addDelRoom(db);
            break;
        case 5:
            admin->matchRoommates(db);
            break;
        case 6:
            admin->cleanRoom(db);
            break;
        case 7:
            cout << "Logging out" << admin->getUserName() << endl;
            admin->logout();
            return;
        default:
            cout << "Wrong Input, please try again" << endl;
            break;
        }
    }
    return;
}





void start_menu(DataBase db)
{
    int st_num;
    unique_ptr<User> curUser;

    while (1)
    {
        startMenuTemplate();
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
                curUser = Login(db, "admin");
                cout << "Welcome "<< curUser->getuserName() <<", Logged into Administrator" << endl;
                adminMenu(curUser,db);
            }
            else if (st_num == 2)
            {
                curUser = Login(db, "student");
                cout << "Welcome "<< curUser->getuserName() << ", Logged into Student" << endl;
                studentMenu(curUser,db);
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
    int i=0;

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

    // std::cout << db.findOne("student", "m4121", 21) <<1<< std::endl;

    // std::cout << db.findAll("student", "jominjun1") <<2<< std::endl;

    // std::cout << db.findAll("room", "g1071") <<3<< std::endl;
    
    // std::cout << db.findAll("admin", "mw4121") <<4<< std::endl;

    // db.update("student", "2s", "content", 3);
    
    //start_menu(db);    

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
