#include "student.h"
#include <memory>
#include<algorithm>

using namespace std;

Student::Student(std::string stuId, int code, const std::string& userName, const std::string& userID, const std::string& userPW,
    const std::string& class_, const std::string& room,
    const bool gender, const std::string& mateID) : User(userID, userPW, userName), studentId(stuId),
    studentCode(code), gender(gender), roommateID(mateID), classOf(class_), roomId(room)

{
}

std::string Student::getFormattedData() const {
    std::string genderString = gender ? "Male" : "Female";
    return studentId + "," + std::to_string(studentCode) + "," + userName + "," + userID + ","
        + userPW + "," + classOf + "," + genderString + "," + role + "," + roomId + "," + roommateID;

}
/*
�����Ʈ ��û�ϴ� �Լ�
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while (true)
    {
        cout << "To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin >> mateId;
        if (mateId == "0") // 0�� �Է¹����� ���
        {
            cout << "Quiting Register Roommate" << endl;
            return;
        }
        /*
        ***��û�� �����Ʈ�� ���̵� �����ͺ��̽��� �������� �ʴ´ٸ� �ٽ� ����
        ���⼭ ������ �߻��� �� �ִ����� mateId�� "404 Not Founded : out of range"��
        �Է¹����� ������ ����� ������ ���߿� ���������***
        */
        if (db.findOne("student", mateId, 1) != mateId)
        {
            cout << "Wrong input, enter again" << endl;
        }
        else // ��� ���̵� �� �Է��ϸ� //6.3 ������ ��������. �ٵ� �����Ʃ��� �����ϼ���. vector�� ���� ���� ���� �����ε�
        {
            roommateID = mateId;
            db.update("student", db.findOne("student", mateId, 0), userID, 8); //db�� �����Ʈ�� �����Ʈ ������Ʈ
            db.update("student", studentId, mateId, 8);                      //db�� ��û�� �����Ʈ ������Ʈ
            cout << "Now (" << userID << ") will be a roommate with (" << mateId << ") " << endl;
        }
    }

    return;
}


//***�����Ʈ�� ã�Ƴ��� Ư�� �˰����� �ʿ���***
void Student::findRoommate(DataBase db)
{
    
    vector<string> main_survey;
    vector<vector<string>> roommate_survey= db.readSurvey();//survey�� ������ ���� ���� ����
    vector<vector<string>> matchedRoommates;
    int applicantIndex=-1;//��ã������ -1, ã�������� ��ġ Ȯ��
    //������� ��ġ Ȯ��
    for (size_t i = 0; i < roommate_survey.size(); i++) {
        if (roommate_survey[i][0] == "3su") //�ϴ��� ������ ���� �־��
            applicantIndex = i;
    }
    if (applicantIndex != -1) {
        vector<string> applicant_survey = roommate_survey[applicantIndex];
        roommate_survey.erase(roommate_survey.begin() + applicantIndex);
        roommate_survey.insert(roommate_survey.begin(), applicant_survey);
    }
    else {
        cout << "Please enter your information first." << endl;
    }
    //�����Ʈ ��Ī
    vector<pair<int,vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[0][j]) - stoi(roommate_survey[i][j]),2);
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //������ �������� ���� (������ �� ���׺� ������ ������ �ջ�)
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        cout << score.first << " ";
    }
    cout << endl;
    //���
    cout << "Matched roommates:" <<endl;
    int i = 0;
    for (const auto& roommate : matchedRoommates) {
        if (i == 0) {
            cout << endl;
            cout << "your info : " ;
        }
        else {
            cout << "Answer " << i << ": ";
        }
        for (const auto& answer : roommate) {
            cout << answer << " ";
        }
        cout << endl;
        if (i == 0) {
            cout << endl;
            cout << "The most appropriate order of roommates." << endl;
            cout << endl;
        }
        i++;
        if (i == 4) {
            break;
        }
    }
    cout << endl;
    //�����ؾ�����. 1. ������ �����Ʈ �ִ��� ���� Ȯ���ؼ� �� ���Ϳ� ���. 2. ��µǴ� ���뿡 �й� �����ϱ� 3. survey�� student�� �񱳴����ϴ°͵� �ʿ�
    return;
}

/*
�����Ʈ�� �������� ���� ��û�� �� �ִ� �Լ�
*/
void Student::registerRoom(DataBase db)
{
    //�����Ʈ�� ������ �����Ʈ���� ���ϰ� �ٽÿ���� ������
    if (roommateID.length() == 0)
    {
        cout << "No roommate, register a roommate first" << endl;
        return;
    }

    string regroomId; // �Է¹��� ��û�� ���ڿ�

    while (true)
    {
        cout << "Enter a Room to Register (Enter 0 to quit): ";
        cin >> regroomId;
        // 0�� �Է¹����� ���
        if (regroomId == "0")
        {
            cout << "Quiting Register Room" << endl;
            return;
        }
        //�����ͺ��̽�(room.txt)���� ã�ƿ� isEmpty�� true �� ��������� ��û����
        if (db.findOne("room", regroomId, 2) == "true")
        {
            if (roomId.length() != 0) // ������ �����ϰ� �ִ� ���� ������
            {
                //***�ڽŰ� �����Ʈ�� ��û ���� ""���� �ʱ�ȭ�ϰ�***
                //***�� ���� ������ ��������***
            }
            roomId = regroomId; // ��û���� �� ���ڿ��� �̰ŷ� �ٲ�
            db.update("room", db.findOne("room", regroomId, 0), "false", 2); // ��û ���� isEmpty�� false�� �ٲ۴�
            db.update("student", db.findOne("student", studentId, 0), regroomId, 6); // ��û �л��� ����� ���� �ٲ۴�
            db.update("student", db.findOne("student", roommateID, 0), regroomId, 6); // ��û �л��� ����� ����� ���� �ٲ۴�.
            cout << "Room successfully registered to (" << roomId << ") with roommate (" << roommateID << ") " << endl; // ���� ����
            return;
        }
        // ���� �̹� ���ִٸ� ������ �ٽ� ������ �ٽ� ������ �� �ֵ��� ���ش�
        else
        {
            cout << "Room is already full " << endl;
            cout << "Try another room" << endl;
        }
    }
    return;
}

/*
�л��� ó�� ȸ������/������ ��, �����Ʈ ��Ī�� ���� Ư�� �������� �Է� �޴� �Լ�
*/
void Student::insertInfo(DataBase db)
{
    cout << "Insert the default information of your life style" << endl;
    cout << "To find the roommate matches with you" << endl;
    vector<string> stuInfo; //�л������� ��� ����
    vector<string> questions{ "Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                "Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                "Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                "Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                "Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
    }; // ���ǻ� ���� ������ ���� 
    int checkNum; // �Է� ����
    int idx = 0; // 0���� �������� ũ�� ��ŭ Ŀ�� Ŀ�� ����

    while (idx != questions.size())
    {
        try { // �Է¹޴� �������� ����̵��� ������ �ƴ϶� �ٸ��� �Է¹޴� ������ �߻� ����
            cout << questions.at(idx);
            cin >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // 1,2,3,4,5,6,7,8, ��
            idx++; // ���� ��������
        }
        catch (const exception& e) // ���� Ȯ��
        {
            cerr << e.what() << endl;
        }
    }

    //***stuInfo�� ������Ʈ�� �����ϴ� ������ �ʿ�*** 
    // stuInfo�� ����� �� "1, 2, 3, 4" ó�� ,�� �鰡�鼭 string���·� ����Ǳ⿡ ������ string������.

    stuInfo.pop_back();// �ǵ� , ����
    db.insertSurvey(stuInfo);
    //***stuInfo�� ������Ʈ�� �����ϴ� ������ �ʿ�***


    return;
}


//�α׾ƿ� ��?��
void Student::logout()
{
    cout << "logging out" << endl;
    return;
}


bool Student::isInfo()
{
    //***�����ʿ�***
    if (studentId.length() != 0) return true;
    else return false;
}

void Student::checkRoom(DataBase db) //�� ���� Ȯ���ϱ� �� ��ȣ�� ���� ���
{
    int datamore = 0;
    string numbers;
    int number=11;
    cout << "check Room Data"<<endl;
    while (true) {
        cout << endl;
        for (int i = 0; i < 10; i++) {//10���� ��� ���.
            numbers = to_string(number) + "r";
            cout<<"Room number " << db.findOne("room", numbers, 1);
            if (db.findOne("room", numbers, 2) == "true") { //���� ����ִٸ�.
                cout << " is empty!" << endl;
            }
            else if(db.findOne("room", numbers, 2) == "false") { //���� ������� ������
                cout << " is not empty." << endl;
            }
            numbers = "";
            number += 1;
        }
        cout << endl;
        cout << "if you want more data enter 1. to exist is 0: ";
        cin >> datamore;
        if (datamore ==0) {
            cout << "over" << endl;
            return;
        }

    }

    //�����
    return;
}

string Student::getUserName()
{
    return userName;
}


void Student::addDelStudents(DataBase db) { return; }
void Student::addDelRoom(DataBase db) { return; }
void Student::matchRoommates(DataBase db) { return; }
void Student::cleanRoom(DataBase db) { return; }
void Student::printInfo() { return; }
void Student::checkStudents(DataBase db) { return; }