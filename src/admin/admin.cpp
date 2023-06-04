// admin.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "admin.h"

using namespace std;

int count_admin = 0;

Admin::Admin( const std::string& userName, const std::string& userID, const std::string& userPW)
    : User(userID, userPW, userName)

{
}

std::string Admin::getFormattedData() const {
    count_admin++;
    std::string a = "a";
    std::string adminId = std::to_string(count_admin) + a;
    return  adminId + "," + userName + "," + userID + "," + userPW + "," + role;
}


/*
현재 기숙사 방들의 현황을 확인할 수 있다
학생들보다 더 자세한 정보들을 볼 수 있다
특정 방에 누가 살고 있는지 등
*/
void Admin::checkRoom(DataBase db)
{

    return;
}
/*
전학생등 특정 회원가입이 힘든 사람들의 정보를 미리 데이터베이스에 입력하는 함수
*/
void Admin::addDelStudents(DataBase db)
{
    
    string selection;
    while (true)
    {
        cout<< "To add students Enter (1), to delete students Enter (2), to quit Enter (0) :";
        cin >> selection;
        if(selection =="0")
        {
            cout << "Quiting Add/Del students "<<endl;
            return;
        }
        else if(selection == "1") // adding student
        {
            vector<string> userInfo;
            vector<string> questions = {"Enter student Name (Enter 0 to exit): ",
                                        "Enter student Code (Enter 0 to exit): ",
                                        "Enter student ID (Enter 0 to exit): ",
                                        "Enter student PW (Enter 0 to exit): ",
                                        "Enter student gender (Enter 0 to exit): "
                                        };
            while(true)
            {
                userInfo.clear();
                string ans;
                int len = questions.size();
                for(int i=0; i<len; i++)
                {
                    cout << questions.at(i);
                    cin  >> ans;
                    if (ans == "0") return;
                    userInfo.push_back(ans);
                }
                cout << " Name  Code  ID  PW  Gender "<<endl;
                for(const auto& info : userInfo)
                {
                    cout << info << ", ";
                }cout <<endl;
                cout << "Will you add this new student? Yes(Y) NO(N) : ";
                cin  >> ans;
                if (ans == "Y" || ans =="y")
                {
                    bool gender;
                    if (userInfo.at(4) == "M") gender = true;
                    if (userInfo.at(4) == "W") gender = false;
                    db.addingStudent(stoi(userInfo.at(1)), userInfo.at(0), userInfo.at(2), userInfo.at(3),"","",gender,"");
                    
                }
                else
                {
                    cout << "Failed adding student" << endl;
                    continue;
                }
                cout << "Successfully Added student " << userInfo.at(0) <<endl;
                return;
            }
        }
        else if(selection == "2")
        {
            //추가해야함
            return;
        }
        else
        {
            cout << "Wrong input, try again : " <<endl;
        }
    }
    return;
}
/*
기숙사 확장 축소 등 상황들이 발생할때 방들을 늘리고 줄이는 함수
*/
void Admin::addDelRoom(DataBase db)
{
    return;
}
/*
룸메이트가 없는 사람들을 룸메이트를 만들어주고 방에 집어넣어주는 함수
*/
void Admin::matchRoommates(DataBase db)
{


    return;
}
/*
기숙사 전체를 비워버려 초기화 해주는 함수
*/
void Admin::cleanRoom(DataBase db)
{
    return;
}

/*
로그아웃 몰?루
*/
void Admin::logout()
{
    return;
}

void Admin::checkStudents(DataBase db)
{
    return;
}

void Admin::registerRoommate(DataBase db){return;}
void Admin::findRoommate(DataBase db){return;}
void Admin::registerRoom(DataBase db){return;}
void Admin::insertInfo(DataBase db){return;}
void Admin::printInfo(){return;}

bool Admin::isInfo(){return false;}
string Admin::getUserName(){return "";}