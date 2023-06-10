// admin.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include<algorithm>
#include "admin.h"
#include "./room/room.h"

using namespace std;

int count_admin = 0;

Admin::Admin(const std::string& userName, const std::string& userID, const std::string& userPW)
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
void Admin::checkRoom(DataBase db) //���� �ȵ����� checkroom,student ��������
{
    int datamore = 0;
    string numbers;
    int number = 0;
    string zone;
    string roommate;
    string roommateid;
    int floor;
        int count = 0;

    while (true) {
        if (count == 0) {
            cout << "Which zone do you want to see first.(g, i, s, t): "; //��� ��������
            cin >> zone;
            cout << "Which floor do you want to see(2~6): "; //��������
            cin >> floor;
            cout << "check Room Data" << endl;
            cout << endl;
        }
        numbers = zone + to_string(floor * 100 +count);
        if (db.findOne("room", numbers, 1) != numbers) {
            cout << "no more room in here." << endl;
            cout << endl;
            cout << "Do you want information on another room? enter 1. to exist is 0: ";
            cin >> datamore;
            if (datamore == 1) {
                count = 0;
                continue;
            }
            else {
                return;
            }
        }
        cout << "Room number " << db.findOne("room", numbers, 1);
        if (db.findOne("room", numbers, 2) == "true") { //���� ����ִٸ�.
            cout << " is empty!" << endl;
        }
        else if (db.findOne("room", numbers, 2) == "false") { //���� ������� ������
            roommate = db.findOne("student", db.findOne("room", numbers, 0), 9);
            roommateid = roommate.replace(roommate.find("m"), 1, "s");
            cout << " was applied by " << db.findOne("student", db.findOne("room", numbers, 0), 1)
                << "," << db.findOne("student", roommateid, 1) << endl;
        }
        numbers = "";


        count++;
        if (count % 10 == 0) { //10�� ������ ��� �� �����ΰ�
            cout << "if you want more data enter 1. to exist is 0: ";
            cin >> datamore;
            cout << endl;
            if (datamore == 0) {
                cout << "thank you." << endl;
                return;
            }
        }


    }

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
        cout << "To add students Enter (1), to delete students Enter (2), to quit Enter (0) :";
        cin >> selection;
        if (selection == "0")
        {
            cout << "Quiting Add/Del students " << endl;
            return;
        }
        else if (selection == "1") // adding student
        {
            vector<string> userInfo;
            vector<string> questions = { "Enter student Name (Enter 0 to exit): ",
                                        "Enter student Code (Enter 0 to exit): ",
                                        "Enter student ID (Enter 0 to exit): ",
                                        "Enter student PW (Enter 0 to exit): ",
                                        "Enter student gender (Enter 0 to exit): "
            };
            while (true)
            {
                userInfo.clear();
                string ans;
                int len = questions.size();
                for (int i = 0; i < len; i++)
                {
                    cout << questions.at(i);
                    cin >> ans;
                    if (ans == "0") return;
                    userInfo.push_back(ans);
                }
                cout << " Name  Code  ID  PW  Gender " << endl;
                for (const auto& info : userInfo)
                {
                    cout << info << ", ";
                }cout << endl;
                cout << "Will you add this new student? Yes(Y) NO(N) : ";
                cin >> ans;
                if (ans == "Y" || ans == "y")
                {
                    bool gender;
                    if (userInfo.at(4) == "M") gender = true;
                    if (userInfo.at(4) == "W") gender = false;
                    db.addingStudent(stoi(userInfo.at(1)), userInfo.at(0), userInfo.at(2), userInfo.at(3), "", "", gender, "");

                }
                else
                {
                    cout << "Failed adding student" << endl;
                    continue;
                }
                cout << "Successfully Added student " << userInfo.at(0) << endl;
                return;
            }
        }
        else if (selection == "2")
        {
            string studentcode;
            string check;
            cout << "Enter student information to delete (ex:20225000): ";
            cin >> studentcode;
            cout <<"student info: " << db.findAll("student", studentcode) << endl;;
            cout << "Are you sure you want to erase the student's information above? (Y/N): ";
            cin >> check;
            string studentid= db.findOne("student", studentcode, 0);
            if (check == "y" || check == "Y") {

                if (db.findOne("student", studentcode, 9) != "404 Not Founded : out of range")//���� �����Ʈ�� �ִٸ�
                {
                    string mateid = db.findOne("student", studentcode, 9);
                    string mateid2 = mateid.replace(mateid.find("m"), 1, "s");

                    db.update("student", mateid, ",", 9);//�������� �����.
                    if (db.findOne("student", studentcode, 8) != "404 Not Founded : out of range")//���� ��û�ߴٸ�
                    {
                        db.update("student", mateid, "", 8);
                        db.update("room", db.findOne("student", studentcode, 8), "true", 2);
                    }
                }
                db.Delete("student", studentid);

                //for (int i = 0; i < 11; i++) {
                //    //cout << db.findOne("student", surveyid, i)<<endl;
                //    db.update("student", studentid, "", 10-i);//���� �ִ����� �� �ִ´�.
                //}
                cout << "The student's information has been cleared." << endl;
            }
            else {
                return;
            }
            //�߰��ؾ���
            //�л� ������ ����� ����
            return;
        }
        else
        {
            cout << "Wrong input, try again : " << endl;
        }
    }
    return;
}
/*
����� Ȯ�� ��� �� ��Ȳ���� �߻��Ҷ� ����� �ø��� ���̴� �Լ�
*/
void Admin::addDelRoom(DataBase db)
{
    string selection;
    while (true) {
        cout << "To add room Enter (1), to delete room Enter (2), to quit Enter (0) :";
        cin >> selection;
        if (selection == "1") {
            string zone;
            int floor;
            //���� ��� ������ �߰��� ���ΰ�
            cout << "Which zone do you want to add first.(g, i, s, t): ";
            cin>> zone;
            cout << "Which floor do you want to add (2~6): "; //��������
            cin >> floor;
            int i = 1;
            string roomnumber = zone + to_string(floor * 100 + i);
            while (db.findOne("room", roomnumber, 1) == roomnumber) {
                 roomnumber = zone + to_string(floor * 100 + i);

                if (db.findOne("room", roomnumber, 1) != roomnumber) {//�� ������ ���ٸ�
                    cout << db.findOne("room", roomnumber, 1) << endl;
                    cout << "The addition room is " << roomnumber<<endl;
                    vector<unique_ptr<Room>> roomdata = db.room_JSON(roomnumber, true);
                    db.insert(roomdata, "room"); // �����߰�
                    return;
                }
                i++;


            }
            return;

        }
        else if (selection == "2") {
            //���� ��� �� ���� ���������(�����Ұ�����)
            string roomnumber;
            cout << "Which room do you want to delete (ex: g200): ";
            cin >> roomnumber;
            if (db.findOne("room", roomnumber, 1) != roomnumber) {
                cout << "Invalid input." << endl;
                return;
            }
            else{
                cout << "Do you want to erase " << roomnumber << "? (Y/N)"; //�� ���� ������ ������ ������ΰ�?
                string check;
                cin >> check;
                string roomid = db.findOne("room", roomnumber, 0);
                if (check == "Y" || check == "y") {
                    db.Delete("room", roomid);
                    cout << "Room's information has been cleared about" <<roomnumber<< endl;
                }
                else {
                    return;
                }
            }
        }
        else {
            return;
        }
    }
    return;
}
/*
�����Ʈ�� ���� ������� �����Ʈ�� ������ְ� �濡 ����־��ִ� �Լ�
*/
void Admin::matchRoommates(DataBase db)
{
    vector<string> main_survey;
    vector<vector<string>> roommate_survey = db.readSurvey();//survey�� ������ ���� ���� ����
    vector<vector<string>> matchedRoommates;
    vector<vector<string>> noRoommate;
    vector<string> rmmate;

    //�����Ʈ ��Ī 
    vector<pair<int, vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[i][j]), 2)*j;//j�� ����ġ ������ �ڷ� ������ ȣ��ȣ �����°�
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //������ �������� ���� (������ �� ���׺� ������ �ջ�) �̸� �������� ����� ������⸮ ����
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        cout << score.first << " ";
    }
    cout << endl;
    //���
    cout << "Matched roommates:" << endl;
    int i = 0;
    int index = 0;
    bool check = 0; //�����Ʈ �ִ��� Ȯ�ο� 
    for (const auto& roommate : matchedRoommates) {//���ĵ� ������ �� �����Ʈ ���� ����� ���� ����
        if (db.findOne("student",  roommate[0], 8) == "404 Not Founded : out of range"
            || db.findOne("student", roommate[0], 8) == "") { //�� ����� �����Ʈ�� ���� ��츸 ���Ϳ� ��´�.
            noRoommate.push_back(roommate);
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }
    for (const auto& roommate : noRoommate) {//���ĵ� ������ �� �����Ʈ ���� ����� ���� ����
        if (i == 0) {
            rmmate = roommate;
            i = 1;
        }
        else if (i == 1) {
            cout << rmmate[0] << " " << roommate[0] << endl;
            cout << rmmate[1] << " " << roommate[1] << endl;
            string studentid = db.findOne("student", rmmate[0], 0);
            string roommateid = db.findOne("student", roommate[0], 0);
            string studentid9= studentid.replace(studentid.find("s"), 1, "m");
            string roommateid9 = roommateid.replace(roommateid.find("s"), 1, "m");
            studentid.replace(studentid.find("m"), 1, "s");
            roommateid.replace(roommateid.find("m"), 1, "s");
            
            //cout << studentid << roommateid << studentid9 << roommateid9 << endl;

            db.update("student", studentid, roommateid9, 9); //db�� �����Ʈ�� �����Ʈ ������Ʈ
            db.update("student", roommateid, studentid9, 9); //db�� ��û�� �����Ʈ ������Ʈ
            
            //�浵 �������� ���⼭ �־������?
            i = 0;
            int room = 11;
            string roomid = to_string(room) + "r";
            //����ִ� ���� �ƹ��ų� ã�Ƽ� �־��ش�.
            while (db.findOne("room", roomid, 2) !="true") {//����ִ� ���� ã�´�.
                room += 1;
                roomid = to_string(room) + "r";
            }
            //cout << roomid << endl;
            db.update("room", db.findOne("room", roomid, 0), "false", 2); // ��û ���� isEmpty�� false�� �ٲ۴�
            db.update("student", db.findOne("student", studentid, 0), db.findOne("room", roomid, 0), 8); // ��û �л��� ����� ���� �ٲ۴�
            db.update("student", db.findOne("student", roommateid, 0), db.findOne("room", roomid, 0), 8); // ��û �л��� ����� ����� ���� �ٲ۴�.
            cout << "Room successfully registered to (" << db.findOne("student",rmmate[0],1) 
                << ") with roommate (" << db.findOne("student",roommate[0],1) << ") in " 
                <<db.findOne("room",roomid,1) <<". " << endl; // ���� ����

            
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }

    //�����Ʈ ��û�Լ�ó�� �� �����͸� �ϳ��ϳ� �ֱ�
    return;
    //vector<vector<string>> noroomate_student;//�����Ʈ�� ���� �л����� ���� ����
    //vector<vector<string>>noroommate_survey;//�����Ʈ�� ���� �л����� info

    //�����Ʈ ���� ������� ������ ���� ���ͷ� ����
    //�� ����ϰ� ������ ���̰� ����ѳ𳢸� ��Ī
    //������ �� ������� �����ؼ� �ΰ��� ��� ��Ī
        
    return;
}
/*
����� ��ü�� ������� �ʱ�ȭ ���ִ� �Լ�
*/
void Admin::cleanRoom(DataBase db) //�� room�� 2��° ���� �� true�� �ʱ�ȭ +student�� ��û ������ ��������
{
    int i = 11;
    while (db.findOne("student", to_string(i)+"r", 0) != "404 Not Founded : out of range") {
        string s = to_string(i) + "r";
        if (db.findOne("room", s, 2) == "false") { //�濡 ���� �������
            db.update("room", s, "true", 2); //���� ����
            string ss = db.findOne("student", s, 0);
            db.update("student", ss, "", 8); //�л����� �濡 ���� ������ ����
            string rs = db.findOne("student", s, 9);
            rs.replace(rs.find("m"), 1, "s");
            db.update("student", rs, "", 8);
        }
        i++;

    }
    return;
}

/*
�α׾ƿ� ��?��
*/
void Admin::logout()
{
    cout << "logging out" << endl;
    return;
}

void Admin::checkStudents(DataBase db) //checkroom���� �л��� ���� ���
{
    string choose;
    //�������� ����. ��ü���� ������ �����͸� ���������, Ư�� �л��� �����͸� ���������
    cout << "choose the case you want" << endl;
    cout << "1. Overall student information" << endl;
    cout << "2. Information about specific students" << endl;
    cout << "Please enter a number. (exist 0): ";
    cin >> choose;

    if (choose == "1") {
        int i = 1;
        string check;
        while (db.findOne("student", to_string(i) + "su", 2) != "404 Not Founded : out of range") {
            cout << "student" << db.findAll("student", to_string(i) + "su")<<endl;
            if (i % 5 == 0) {
                cout << "Would you like to see more information? (Y/N) :";
                cin >> check;
                if (check == "y" || check == "Y") {
                    i++;
                    continue;
                }
                else {
                    return;
                }

            }
            i++;

        }
        return;
        //���� �� ��������ϴϱ� �����Ʈ ������ ���� ������ ���� �ִ��� ����������
        //5���� ��� �� ���� ������ �������� checkroom������
    }
    else if (choose == "2") {
        int int_studentcode;
        cout << "Please enter the student's code: ";
        cin >> int_studentcode;
        string studentcode = to_string(int_studentcode);
        if (db.findOne("student", studentcode, 0) == "404 Not Founded : out of range") {
            cout << "This is a student who is not registered as a member." << endl;
            return;
        }
        cout << db.findAll("student", studentcode);
        if (db.findOne("student", studentcode, 9) != "404 Not Founded : out of range")//���� �����Ʈ�� �ִٸ�
        {
            string mateid = db.findOne("student", studentcode, 9);
            mateid = mateid.replace(mateid.find("m"), 1, "s");
            cout << "student has roommate."<<endl;
            cout << "roommate's code is " << db.findOne("student", mateid, 1)<<"."<<endl;
            if (db.findOne("student", studentcode, 8) != "404 Not Founded : out of range")//���� ��û�ߴٸ�
            {
                cout << "They applied for a room " 
                    << db.findOne("room", db.findOne("student", studentcode, 8), 1)<<". "<<endl;//�� ��ġ

             }
            else {
                cout << "They didn't apply for a room."<<endl;
            }
        }
        else {
            cout << "student doesn't have roommate." << endl;
        }
        //�й�,�л�,���������,�����Ʈ����,������ ��� ��� �������� �߰��ؾ���

    }
    else {
        return;
    }
    return;
}

void Admin::registerRoommate(DataBase db) { return; }
void Admin::findRoommate(DataBase db) { return; }
void Admin::releaseRoommate(DataBase db) { return; }
void Admin::registerRoom(DataBase db) { return; }
void Admin::releaseRoom(DataBase db) { return; }
void Admin::insertInfo(DataBase db) { return; }
void Admin::printInfo() { return; }

bool Admin::isInfo() { return false; }
string Admin::getUserName() { return ""; }