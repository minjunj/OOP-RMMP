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
���� ����� ����� ��Ȳ�� Ȯ���� �� �ִ�
�л��麸�� �� �ڼ��� �������� �� �� �ִ�
Ư�� �濡 ���� ��� �ִ��� ��
*/
void Admin::checkRoom(DataBase db)
{

    return;
}
/*
���л��� Ư�� ȸ�������� ���� ������� ������ �̸� �����ͺ��̽��� �Է��ϴ� �Լ�
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
            //�߰��ؾ���
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
����� Ȯ�� ��� �� ��Ȳ���� �߻��Ҷ� ����� �ø��� ���̴� �Լ�
*/
void Admin::addDelRoom(DataBase db)
{
    return;
}
/*
�����Ʈ�� ���� ������� �����Ʈ�� ������ְ� �濡 ����־��ִ� �Լ�
*/
void Admin::matchRoommates(DataBase db)
{


    return;
}
/*
����� ��ü�� ������� �ʱ�ȭ ���ִ� �Լ�
*/
void Admin::cleanRoom(DataBase db)
{
    return;
}

/*
�α׾ƿ� ��?��
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