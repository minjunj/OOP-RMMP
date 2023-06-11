#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <memory>
#include "./user/User.h"
#include "./database/DataBase.h"
#include "./student/student.h"
#include "./admin/admin.h"
#include "./room/room.h"
#include "./templates.h"
using namespace std;
using JsonStu = std::vector<std::unique_ptr<Student>>;
using JsonAdmin = std::vector<std::unique_ptr<Admin>>;
using JsonRoom = std::vector<std::unique_ptr<Room>>;

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
    cout << db.findOne("survey", student->getsurveyId(), 0) << endl;
    if (student->getsurveyId() !="NULL")
    {
        int menuNum;
        while (1)
        {
            studentMenuTemplate1();
            cout << ">> Enter the Number to use : ";
            cin >> menuNum;
            while(cin.fail()){
                cout << "** Wrong input try again"<<endl;
                cin.clear();
                cin.ignore(100 ,'\n');
                cout << ">> Enter the Number to use : ";
                cin  >> menuNum;
            }
            switch (menuNum)
            {
            case 1:
                student->registerRoommate(db);
                break;
            case 2:
                student->findRoommate(db);
                break;
            case 3:
                student->releaseRoommate(db);
                break;
            case 4:
                student->checkRoom(db); // DataBase에서 새로 들어줘야할 함수, 현재 기숙사의 전체적인 현황(비어있는지, 방에 몇명 있는지 등) 한 눈에 볼 수 있는 함수가 필요
                break;
            case 5:
                student->registerRoom(db);
                break;
            case 6:
                student->releaseRoom(db);
                break;
            case 7:
                cout << student->getFormattedData() << endl;
                break;
            case 8:
                student->insertInfo(db);
                break;
            case 9:
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
            while(cin.fail()){
                cout << "** Wrong input try again"<<endl;
                cin.clear();
                cin.ignore(100 ,'\n');
                cout << ">> Enter the Number to use : ";
                cin  >> menuNum;
            }
            switch (menuNum)
            {
            case 1:
                student->insertInfo(db);
                cout << ">> Logout and Login again to continue" <<endl;
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
        while(cin.fail()){
            cout << "** Wrong input try again"<<endl;
            cin.clear();
            cin.ignore(100 ,'\n');
            cout << ">> Enter the Number to use : ";
            cin  >> menuNum;
        }
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
        cout << " Name    "<<" Code   "<<"   ID   "<< "    PW    "<< "chPW  " << "    Gender   " << endl;
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
        while(cin.fail()){
            cout << "** Wrong input try again"<<endl;
            cin.clear();
            cin.ignore(100 ,'\n');
            cout << ">> Enter the number here (1~4) : ";
            cin  >> st_num1;
        }

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
#endif