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
    cout << "|            to Sign in / up               |" << endl;
    cout << "|                                          |" << endl;
    cout << "|            1. Student Sign up            |" << endl;
    cout << "|            2. Admin Login                |" << endl;
    cout << "|            3. Student Login              |" << endl;
    cout << "|            4. Exit                       |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "+------------------------------------------+" << endl;
    return;
}
void studentMenuTemplate1()
{
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
unique_ptr<User> Login(DataBase db, string userType)
{
    string file;
    string userId, userPw;

    while (1)
    {
        cout << ">> Enter User ID : ";
        cin >> userId;
        cout << ">> Enter the User Password : ";
        cin >> userPw;

        if (db.findUser(userType, userId, userPw))
        {
            return db.getUser(userType, userId, userPw);
        }
        else
        {
            cout << "\n** Wrong ID or password, try again\n" << endl;
        }
    }
}
void studentMenu(unique_ptr<User>& student, DataBase db)
{
    if (db.findOne("survey",student->getsurveyId() , 0) != "404 Not Founded : out of range")
    {
        int menuNum;
        while (1)
        {
            studentMenuTemplate1();
            cout << ">> Enter the Number to use : ";
            cin >> menuNum;
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
                cout << ">> Logging out" << student->getUserName() << endl;
                return;
            default:
                cout << "** Wrong Input, please try again" << endl;
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
            cout << ">> Enter the Number to use : ";
            cin >> menuNum;
            switch (menuNum)
            {
            case 1:
                student->insertInfo(db);
                break;
            case 2:
                cout << ">> Logging out" << student->getUserName() << endl;
                return;
            default:
                cout << "** Wrong Input, please try again" << endl;
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
        cout << ">> Enter the Number to use : ";
        cin >> menuNum;
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
            cout << ">> Logging out" << admin->getUserName() << "\n" << endl;
            return;
        default:
            cout << "** Wrong Input, please try again" << endl;
            break;
        }
    }
    return;
}

void studentSignUp(DataBase db)
{
    cout << "++ To Sign up to the program Enter your personal data ++" << endl;
    vector<string> questions = { ">> Enter student Name (Enter 0 to exit): ",
                                ">> Enter student Code (Enter 0 to exit): ",
                                ">> Enter student ID (Enter 0 to exit): ",
                                ">> Enter student PW (Enter 0 to exit): ",
                                ">> Enter student PW again (Enter 0 to exit): ",
                                ">> Enter student gender ( M: Man/W: Woman , Enter 0 to exit): "
    };
    vector<string> userInfo;
    while (true)
    {
        userInfo.clear();
        string ans;
        int len = questions.size();
        int idx = 0;
        while (idx < len)
        {
            cout << questions.at(idx);
            cin >> ans;
            if (ans == "0") 
            {
                cout << "\n** Exiting Sign Up" <<endl;
                cout << "** Going Back to Main Menu\n"<<endl;
                return;
            }
            if (idx == 2 && db.findOne("student", ans, 3) == ans)
            {
                idx--;
                cout << "** Wrong input, ID already exists " << endl;
            }
            else if (idx == 4 && ans != userInfo.at(3))
            {
                idx--;
                cout << "** Wrong input, check PW again " << endl;
            }
            else
            {
                idx++;
                userInfo.push_back(ans);
            }
            
        }
        cout << " Name    "<<"   Code   "<<"   ID   "<< "    PW    "<<   "    Gender   " << endl;
        cout << "==================================================="<<endl;
        cout << "|";
        for (const auto& info : userInfo)
        {
            cout << info << " | ";
        }cout << endl;
        cout << ">> Will you Sign up as student " << userInfo.at(2) << " ? Yes(Y) NO(N) : ";
        cin >> ans;
        if (ans == "Y" || ans == "y")
        {
            bool gender=0;

            if (userInfo.at(5) == "M") gender = true;
            if (userInfo.at(5) == "W") gender = false;

            db.addingStudent(stoi(userInfo.at(1)), userInfo.at(0), userInfo.at(2), userInfo.at(3), "", "", gender, "");
        }
        else
        {
            cout << ">> Failed signing up" << endl;
            return;
        }
        cout << ">> Successfully Signed up " << endl;
        cout << ">> To use the program, login again" << endl;
        break;
    }
    return;
}


void start_menu(DataBase db)
{
    int st_num;
    string st_num1; // 기존의 int로 입력받으면 문자가 들어왔을때 무한루프함 string으로 받아서 해결
    unique_ptr<User> curUser;

    while (1)
    {
        
        startMenuTemplate();
        cout << ">> Enter the number here (1~4) : ";
        cin >> st_num1;


        if (st_num1 != "1" && st_num1 != "2" && st_num1 != "3" && st_num1 !="4")
        {
            cout << "\n** Wrong input, try again\n" << endl;
            continue;
        }
        else
        {
            st_num = stoi(st_num1);
            if (st_num == 1)
            {
                studentSignUp(db);
            }
            else if (st_num == 2)
            {
                curUser = Login(db, "admin");
                cout << ">> Welcome " << curUser->getuserName() << ", Logged into Administrator\n" << endl;
                adminMenu(curUser, db);
            }
            else if (st_num == 3)
            {
                curUser = Login(db, "student");
                cout << ">> Welcome " << curUser->getuserName() << ", Logged into Student\n" << endl;
                studentMenu(curUser, db);
            }
            else if (st_num == 4)
            {
                cout << "\n>> Ending program" << endl;
                cout << ">> Thank you for using"<<endl;
                return;
            }
        }
    }
}


void versionCheck()
{
    std::cout << "========================================"<<endl<<endl;
    std::cout << " #####    ##     ##  ##     ##   #####  "<<endl;
    std::cout << " ##   ##  #### ####  #### ####  ##      "<<endl;
    std::cout << " #####    ## ### ##  ## ### ##    ###  "<<endl;
    std::cout << " ##  ##   ##     ##  ##     ##      ##  "<<endl;
    std::cout << " ##   ##  ##     ##  ##     ##  #####   "<<endl<<endl;
    std::cout << "========================================"<<endl;
    std::cout << " V1.0 Roommate Matching System for GIST"<<endl;
    std::cout << " Built By Hyunwoo Lee, Minjun Jo, Minjae Jo"<<endl<<endl;
}


int main()
{
    DataBase db;
    int i=0;
    //JsonStu studentData = db.student_JSON(20225180, "조민준", "m412", "pw12", "22", "2a", true, "3s", "1su"); 
    //JsonAdmin adminData = db.admin_JSON("조민준", "mw412", "pww12");
    JsonRoom roomData = db.room_JSON("g107", true);
    //db.insert(studentData, "student"); //db에 삽입
    //db.insert(adminData, "admin");
    db.insert(roomData, "room");

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

    //std::cout << db.findOne("survey", "1su", 0) <<1<< std::endl;

    // std::cout << db.findAll("student", "jominjun1") <<2<< std::endl;

    //std::cout << db.findAll("room", "g1071") <<3<< std::endl;
    
    // std::cout << db.findAll("admin", "mw4121") <<4<< std::endl;

    // db.update("student", "2s", "content", 3);
    vector<string> list;
    list = {"a", ",", "s", ",", "22"};

    // db.insertSurvey(list);
    versionCheck();
    start_menu(db);    
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
