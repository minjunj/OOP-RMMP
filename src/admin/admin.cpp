// admin.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include<algorithm>
#include "admin.h"
#include "../room/room.h"
#include <cmath>

using namespace std;


Admin::Admin(std::string adminId, const std::string& userName, const std::string& userID, const std::string& userPW)
    : User(userID, userPW, userName), adminId(adminId) 
{
}

std::string Admin::getFormattedData() const {
    
    return  adminId + "," + userName + "," + userID + "," + userPW + "," + role;
}

/*
현재 기숙사 방들의 현황을 확인할 수 있다
학생들보다 더 자세한 정보들을 볼 수 있다
특정 방에 누가 살고 있는지 등
*/
void Admin::checkRoom(DataBase db) //아직 안돌려봄 checkroom,student 마찬가지
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
            cout << ">> Which zone do you want to see first.(g, i, s, t): "; //어느 구역인지
            cin >> zone;
            cout << ">> Which floor do you want to see(2~6): "; //몇층인지
            cin >> floor;
            while(cin.fail()){
                cout << "** Wrong input try again"<<endl;
                cin.clear();
                cin.ignore(100 ,'\n');
                cout << ">> Which floor do you want to see(2~6): "; //몇층인지
                cin >> floor;
            }
            cout << ">> check Room Data" << endl;
            cout << endl;
        }
        numbers = zone + to_string(floor * 100 +count);
        if (db.findOne("room", numbers, 1) != numbers) {
            cout << ">> no more room in here." << endl;
            cout << endl;
            cout << ">> Do you want information on another room? enter 1. to exist is 0: ";
            cin >> datamore;
            if (datamore == 1) {
                count = 0;
                continue;
            }
            else {
                return;
            }
        }
        cout << ">> Room number " << db.findOne("room", numbers, 1);
        if (db.findOne("room", numbers, 2) == "true") { //방이 비어있다면.
            cout << " is empty!" << endl;
        }
        else if (db.findOne("room", numbers, 2) == "false") { //방이 비어있지 않으면
            roommate = db.findOne("student", db.findOne("room", numbers, 0), 9);
            roommateid = roommate.replace(roommate.find("m"), 1, "s");
            cout << " was applied by " << db.findOne("student", db.findOne("room", numbers, 0), 1)
                << "," << db.findOne("student", roommateid, 1) << endl;
        }
        numbers = "";


        count++;
        if (count % 10 == 0) { //10개 단위로 끊어서 더 볼것인가
            cout << ">> if you want more data enter 1. to exist is 0: ";
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
        cout << ">> To add students Enter (1), to delete students Enter (2), to quit Enter (0) :";
        cin >> selection;
        if (selection == "0")
        {
            cout << "** Quiting Add/Del students " << endl <<endl;
            return;
        }
        else if (selection == "1") // adding student
        {
            vector<string> userInfo;
            vector<string> questions = { ">> Enter student Name (Enter 0 to exit): ",
                                        ">> Enter student Code (Enter 0 to exit): ",
                                        ">> Enter student ID (Enter 0 to exit): ",
                                        ">> Enter student PW (Enter 0 to exit): ",
                                        ">> Enter student gender (M:Man/W:Woman)(Enter 0 to exit): "
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
                cout << "=============================" <<endl;
                for (const auto& info : userInfo)
                {
                    cout << info << ", ";
                }cout << endl;
                cout << ">> Will you add this new student? Yes(Y) NO(N) : ";
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
                    cout << "** Failed adding student" << endl;
                    continue;
                }
                cout << ">> Successfully Added student " << userInfo.at(0) << endl;
                return;
            }
        }
        else if (selection == "2")
        {
            string studentcode;
            string check;
            cout << ">> Enter student information to delete (ex:20225000): ";
            cin  >> studentcode;
            cout << ">> student info: " << db.findAll("student", studentcode) << endl;;
            cout << ">> Are you sure you want to erase the student's information above? (Y/N): ";
            cin >> check;
            if (check == "y" || check == "Y") {
                //����� ����. ������Ʈ�� �� nulló��
                for (int i = 0; i < 10; i++) {
                    if (db.findOne("student", studentcode, 9) != "404 Not Founded : out of range")//���� �����Ʈ�� �ִٸ�
                    {
                        string mateid = db.findOne("student", studentcode, 9);
                        mateid=mateid.replace(mateid.find("m"), 1, "s");
                        db.update("student",mateid,"",9);//�������� �����.
                        if (db.findOne("student", studentcode, 8) != "404 Not Founded : out of range")//���� ��û�ߴٸ�
                        {
                            db.update("student", studentcode, "", 8);//������ �ʱ�ȭ��Ų��.
                            db.update("student", mateid, "", 8);
                            db.update("room", db.findOne("student", studentcode, 8), "true", 2);
                        }
                    }
                    db.update("student", studentcode, "", i);//���� �ִ����� �� �ִ´�.


                }
                cout << endl <<">> The student's information has been cleared." << endl <<endl;
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
            cout << "** Wrong input, try again : " << endl;
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
        cout << ">> To add room Enter (1), to delete room Enter (2), to quit Enter (0) :";
        cin >> selection;
        if (selection == "1") {
            string zone;
            int floor;
            //���� ��� ������ �߰��� ���ΰ�
            cout << ">> Which zone do you want to add first.(g, i, s, t): ";
            cin>> zone;
            cout << ">> Which floor do you want to add (2~6): "; //��������
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

                if (db.findOne("student", studentcode, 9) != "404 Not Founded : out of range")//만약 룸메이트가 있다면
                {
                    string mateid = db.findOne("student", studentcode, 9);
                    mateid = mateid.replace(mateid.find("m"), 1, "s");

                    db.update("student", mateid, "", 9);//공란으로 만든다.
                    if (db.findOne("student", studentcode, 8) != "404 Not Founded : out of range")//방을 신청했다면
                    {
                        db.update("student", mateid, "", 8);
                        db.update("room", db.findOne("student", studentcode, 8), "true", 2);
                    }
                }
                for (int i = 0; i < 11; i++) {
                    //cout << db.findOne("student", surveyid, i)<<endl;
                    db.update("student", studentid, "", 10-i);//원래 있던값에 을 넣는다.


                }
                cout << ">> The student's information has been cleared." << endl;
            }
            else {
                cout << "** Quiting..." << endl;
                return;
            }
            return;
        }
        else if (selection == "0")
        {
            cout << "** Quitting Add/Del students "<< endl;
            return;
        }
        else
        {
            cout << "** Wrong input, Try again " << endl;
        }
    }

    
    return;
}
/*
/*
룸메이트가 없는 사람들을 룸메이트를 만들어주고 방에 집어넣어주는 함수
*/
void Admin::matchRoommates(DataBase db)
{
    vector<string> main_survey;
    vector<vector<string>> roommate_survey = db.readSurvey();//survey의 정보를 전부 담은 벡터
    vector<vector<string>> matchedRoommates;
    vector<vector<string>> noRoommate;
    vector<string> rmmate;

    //룸메이트 매칭 
    vector<pair<int, vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[i][j]), 2)*j;//j는 가중치 문항이 뒤로 갈수록 호불호 갈리는것
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //점수를 기준으로 정렬 (점수는 각 문항별 제곱의 합산) 이를 기준으로 비슷한 점수대기리 포진
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        //cout << score.first << " ";
    }
    cout << endl;
    //출력
    cout << ">> Matched roommates:" << endl;
    int i = 0;
    int index = 0;
    bool check = 0; //룸메이트 있는지 확인용 
    for (const auto& roommate : matchedRoommates) {//정렬된 데이터 중 룸메이트 없는 사람만 따로 저장
        if (db.findOne("student",  roommate[0], 8) == "404 Not Founded : out of range"
            || db.findOne("student", roommate[0], 8) == "") { //그 사람이 룸메이트가 없는 경우만 벡터에 담는다.
            noRoommate.push_back(roommate);
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }
    for (const auto& roommate : noRoommate) {//정렬된 데이터 중 룸메이트 없는 사람만 따로 저장
        if (i == 0) {
            rmmate = roommate;
            i = 1;
        }
        else if (i == 1) {
            //cout << rmmate[0] << " " << roommate[0] << endl;
            //cout << rmmate[1] << " " << roommate[1] << endl;
            string studentid = db.findOne("student", rmmate[0], 0);
            string roommateid = db.findOne("student", roommate[0], 0);
            string studentid9= studentid.replace(studentid.find("s"), 1, "m");
            string roommateid9 = roommateid.replace(roommateid.find("s"), 1, "m");
            studentid.replace(studentid.find("m"), 1, "s");
            roommateid.replace(roommateid.find("m"), 1, "s");
            
            //cout << studentid << roommateid << studentid9 << roommateid9 << endl;

            db.update("student", studentid, roommateid9, 9); //db에 룸메이트의 룸메이트 업데이트
            db.update("student", roommateid, studentid9, 9); //db에 신청자 룸메이트 업데이트
            
            //방도 랜덤으로 여기서 넣어줘야해?
            i = 0;
            int room = 11;
            string roomid = to_string(room) + "r";
            //비어있는 방을 아무거나 찾아서 넣어준다.
            while (db.findOne("room", roomid, 2) !="true") {//비어있는 방을 찾는다.
                room += 1;
                roomid = to_string(room) + "r";
            }
            //cout << roomid << endl;
            db.update("room", db.findOne("room", roomid, 0), "false", 2); // 신청 방의 isEmpty를 false로 바꾼다
            db.update("student", db.findOne("student", studentid, 0), db.findOne("room", roomid, 0), 8); // 신청 학생의 기숙사 방을 바꾼다
            db.update("student", db.findOne("student", roommateid, 0), db.findOne("room", roomid, 0), 8); // 신청 학생의 룸메의 기숙사 방을 바꾼다.
            cout << ">> Room successfully registered to (" << db.findOne("student",rmmate[0],1) 
                << ") with roommate (" << db.findOne("student",roommate[0],1) << ") in " 
                <<db.findOne("room",roomid,1) <<". " << endl; // 정보 공지

            
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }

    //룸메이트 신청함수처럼 위 데이터를 하나하나 넣기
    return;
    //vector<vector<string>> noroomate_student;//룸메이트가 없는 학생들을 담을 벡터
    //vector<vector<string>>noroommate_survey;//룸메이트가 없는 학생들의 info

    //룸메이트 없는 사람들의 정보를 따로 벡터로 저장
    //다 비슷하게 서로의 차이가 비슷한놈끼리 매칭
    //위에서 걍 순서대로 정렬해서 두개씩 끊어서 매칭
        
    return;
}
/*
기숙사 전체를 비워버려 초기화 해주는 함수
*/
void Admin::cleanRoom(DataBase db) //걍 room의 2번째 열을 다 true롤 초기화 +student의 신청 정보도 지워야함
{
    int i = 11;
    int count = 0;
    string s = to_string(i) + "r";

    while (db.findOne("room", to_string(i)+"r", 0) == to_string(i) + "r") {
        string s = to_string(i) + "r";
        //cout << s << db.findOne("room", to_string(i) + "r", 1) << endl;
        if (db.findOne("room", s, 2) == "false") { //방에 누가 있을경우
            if (count == 0) {
                cout << ">> The rooms have been vacated." << endl;
            }

            db.update("room", s, "true", 2); //방을 비우고
            string ss = db.findOne("student", s, 0);
            db.update("student", ss, "", 8); //학생들의 방에 대한 정보도 비운다
            string rs = db.findOne("student", s, 0);
            //cout << s<<ss << rs << endl;
            db.update("student", rs, "", 8);
            cout <<">> "<< db.findOne("room", s, 1) << " Room is empty. (" 
                <<db.findOne("student",ss,1) << ", " <<db.findOne("student",rs,1) << ")" << endl;
            count += 1;
        }
        i++;

    }
    if (count == 0) { // 비울 방이 없을때
        cout << ">> All rooms are empty." << endl;
    }
    return;
}

void Admin::checkStudents(DataBase db) 
{
    string choose;
        cout << ">> Choose the case you want" << endl;
    cout << ">>   1. Overall student information" << endl;
    cout << ">>   2. Information about specific students" << endl;
    cout << ">> Please enter a number. (exit 0): ";
    cin  >> choose;
    cout << endl;
    if (choose == "1") {
        int i = 1;
        string check;
        cout <<endl;
        while (db.findOne("student", to_string(i) + "su", 2) != "") {
            cout << ">> student ";
            db.findAll("student", to_string(i) + "su");
            cout <<endl;
            if (i % 5 == 0) {
                cout << endl;
                cout << ">> Would you like to see more information? (Y/N) : ";
                cin >> check;
                cout <<endl;
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

    }
    else if (choose == "2") {
        int int_studentcode;
        cout << ">> Please enter the student's code: ";
        cin >> int_studentcode;
        string studentcode = to_string(int_studentcode);
        if (db.findOne("student", studentcode, 0) == "") {
            cout << "** This is a student who is not registered as a member." << endl;
            return;
        }
        cout << ">> " << db.findAll("student", studentcode);
        if (db.findOne("student", studentcode, 9) !="404 Not Founded : out of range" )
        {
            cout << endl;
            string mateid = db.findOne("student", studentcode, 9);
            mateid = mateid.replace(mateid.find("m"), 1, "s");
            cout << ">> student has roommate."<<endl;
            cout << ">> roommate's code is " << db.findOne("student", mateid, 1)<<"."<<endl;
            if (db.findOne("student", studentcode, 8) != "")
            {
                cout << ">> They applied for a room " 
                    << db.findOne("room", db.findOne("student", studentcode, 8), 1)<<". "<<endl;

             }
            else {
                cout << ">> They didn't apply for a room."<<endl;
            }
        }
        else {
            cout << ">> student doesn't have roommate." << endl;
        }
    }
    else {
        cout <<"** Quiting chekcing students"<<endl;
        return;
    }
    return;
}

void Admin::registerRoommate(DataBase db) { return; }
void Admin::findRoommate(DataBase db) { return; }
void Admin::registerRoom(DataBase db) { return; }
void Admin::insertInfo(DataBase db) { return; }
void Admin::printInfo() { return; }
void Admin::releaseRoommate(DataBase db) {return;}
bool Admin::isInfo() { return false; }
string Admin::getsurveyId() {return ""; }
string Admin::getUserName() { return ""; }
void Admin::releaseRoom(DataBase db) {return ;}