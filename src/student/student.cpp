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
룸메이트 신청하는 함수
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while (true)
    {
        cout << "To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin >> mateId;
        if (mateId == "0") // 0을 입력받으면 취소
        {
            cout << "Quiting Register Roommate" << endl;
            return;
        }
        /*
        ***신청할 룸메이트의 아이디가 데이터베이스에 존재하지 않는다면 다시 돌림
        여기서 에러가 발생할 수 있는점이 mateId를 "404 Not Founded : out of range"로
        입력받으면 문제가 생기기 때문에 나중에 고쳐줘야함***
        */
        if (db.findOne("student", mateId, 1) != mateId)
        {
            cout << "Wrong input, enter again" << endl;
        }
        else // 룸메 아이디를 잘 입력하면 //6.3 오류를 보긴했음. 근데 비쥬얼스튜디오 문제일수도. vector의 범위 오버 관련 문제인듯
        {
            roommateID = mateId;
            db.update("student", db.findOne("student", mateId, 0), userID, 8); //db에 룸메이트의 룸메이트 업데이트
            db.update("student", studentId, mateId, 8);                      //db에 신청자 룸메이트 업데이트
            cout << "Now (" << userID << ") will be a roommate with (" << mateId << ") " << endl;
        }
    }

    return;
}


//***룸메이트를 찾아내는 특정 알고리즘이 필요함***
void Student::findRoommate(DataBase db)
{
    
    vector<string> main_survey;
    vector<vector<string>> roommate_survey= db.readSurvey();//survey의 정보를 전부 담은 벡터
    vector<vector<string>> matchedRoommates;
    int applicantIndex=-1;//못찾았을때 -1, 찾았을때는 위치 확인
    //사용자의 위치 확인
    for (size_t i = 0; i < roommate_survey.size(); i++) {
        if (roommate_survey[i][0] == "3su") //일단은 임의의 값을 넣어둠
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
    //룸메이트 매칭
    vector<pair<int,vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[0][j]) - stoi(roommate_survey[i][j]),2);
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //점수를 기준으로 정렬 (점수는 각 문항별 차이의 제곱의 합산)
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        cout << score.first << " ";
    }
    cout << endl;
    //출력
    cout << "Matched roommates:" <<endl;
    int i = 0;
    int index = 0;
    bool check = 0; //룸메이트 있는지 확인용
    for (const auto& roommate : matchedRoommates) {
        if (i == 0) {
            cout << endl;
            cout << "your info : " ;
        }
        else {
            cout << "Answer " << i << ": ";
            cout << db.findOne("student", roommate[0], 1); //학번
    //        cout << db.findOne("student", db.findOne("student", roommate[0], 1), 8); //학번
            if (db.findOne("student", db.findOne("student", roommate[0], 1), 8) == "404 Not Founded : out of range") { //그 사람이 룸메이트가 있는가.
                cout << " has no roommate" << endl; //룸메이트 없는 경우에만 출력되도록 설정해야함
                check = 0;
            }
            else {
                check = 1;
                cout << " has roommate" << endl;//여기서 원래라면 continue로 돌아가게 할듯
            }
            cout << "his/her info: ";
        }
        


        for (const auto& answer : roommate) {
            //if (index % 5 != 0) {
            //    cout << answer << " ";
            //}
            //index += 1;
            cout << answer << " ";

        }
        cout << endl<<endl;
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
    return;
}

/*
룸메이트가 있을때만 방을 신청할 수 있는 함수
*/
void Student::registerRoom(DataBase db)
{
    //룸메이트가 없으면 룸메이트부터 구하고 다시오라고 리턴함
    if (roommateID.length() == 0)
    {
        cout << "No roommate, register a roommate first" << endl;
        return;
    }

    string regroomId; // 입력받을 신청방 문자열

    while (true)
    {
        cout << "Enter a Room to Register (Enter 0 to quit): ";
        cin >> regroomId;
        // 0을 입력받으면 취소
        if (regroomId == "0")
        {
            cout << "Quiting Register Room" << endl;
            return;
        }
        //데이터베이스(room.txt)에서 찾아온 isEmpty가 true 즉 비어있을때 신청가능
        if (db.findOne("room", regroomId, 2) == "true")
        {
            if (roomId.length() != 0) // 기존에 차지하고 있던 방이 있으면
            {
                //***자신과 룸메이트의 신청 방은 ""으로 초기화하고***
                //***그 방의 정보를 지워야함***
            }
            roomId = regroomId; // 신청자의 방 문자열은 이거로 바뀜
            db.update("room", db.findOne("room", regroomId, 0), "false", 2); // 신청 방의 isEmpty를 false로 바꾼다
            db.update("student", db.findOne("student", studentId, 0), regroomId, 6); // 신청 학생의 기숙사 방을 바꾼다
            db.update("student", db.findOne("student", roommateID, 0), regroomId, 6); // 신청 학생의 룸메의 기숙사 방을 바꾼다.
            cout << "Room successfully registered to (" << roomId << ") with roommate (" << roommateID << ") " << endl; // 정보 공지
            return;
        }
        // 방이 이미 차있다면 루프를 다시 돌리고 다시 선택할 수 있도록 해준다
        else
        {
            cout << "Room is already full " << endl;
            cout << "Try another room" << endl;
        }
    }
    return;
}

/*
학생이 처음 회원가입/변경할 때, 룸메이트 매칭을 위한 특정 정보들을 입력 받는 함수
*/
void Student::insertInfo(DataBase db)
{
    cout << "Insert the default information of your life style" << endl;
    cout << "To find the roommate matches with you" << endl;
    vector<string> stuInfo; //학생정보가 담길 벡터
    vector<string> questions{ "Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                "Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                "Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                "Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                "Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
    }; // 편의상 만든 질문지 벡터 
    int checkNum; // 입력 정수
    int idx = 0; // 0부터 질문지의 크기 만큼 커질 커서 역할

    while (idx != questions.size())
    {
        try { // 입력받는 과정에서 띨빡이들이 정수가 아니라 다른걸 입력받는 에러가 발생 가능
            cout << questions.at(idx);
            cin >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // 1,2,3,4,5,6,7,8, 꼴
            idx++; // 다음 질문으로
        }
        catch (const exception& e) // 에러 확인
        {
            cerr << e.what() << endl;
        }
    }

    //***stuInfo를 오브젝트에 저장하는 과정이 필요*** 
    // stuInfo가 저장될 떈 "1, 2, 3, 4" 처럼 ,가 들가면서 string형태로 저장되기에 저장은 string으로함.

    stuInfo.pop_back();// 맨뒤 , 제거
    db.insertSurvey(stuInfo);
    //***stuInfo를 오브젝트에 저장하는 과정이 필요***
 

    return;
}


//로그아웃 몰?루
void Student::logout()
{
    cout << "logging out" << endl;
    return;
}


bool Student::isInfo()
{
    //***보완필요***
    //정보가 입력되었는지 확인이 필요함. survey를 입력했을때 있는 'su'가 있는지 확인
    if (studentId=="0") {//surveyid가 들어있는지 확인해야함 수정이 필요
        return false;
    }
    return true;
 
}

void Student::checkRoom(DataBase db) //방 상태 확인하기 방 번호와 상태 출력
{
    int datamore = 0;
    string numbers;
    int number=0;
    string zone;
    int floor;

    while (true) {
        if (datamore == 0) {
            cout << "Which zone do you want to see first.(g, i, s, t): "; //어느 구역인지
            cin >> zone;
            cout << "Which floor do you want to see(2~6): "; //몇층인지
            cin >> floor;
            cout << "check Room Data" << endl;
            cout << endl;
        }

        for (int i = 0; i < 10; i++) {//10개씩 끊어서 출력.
            numbers = zone+to_string(floor*100+i+1+10*datamore);
            if (i + 1 + 10*datamore != 20) { //19호까지 출력
                cout << "Room number " << db.findOne("room", numbers, 1);
                if (db.findOne("room", numbers, 2) == "true") { //방이 비어있다면.
                    cout << " is empty!" << endl;
                }
                else if (db.findOne("room", numbers, 2) == "false") { //방이 비어있지 않으면
                    cout << " is not empty." << endl;
                }
                numbers = "";
            }
            else {//20번째 일때 다른 호실에 대한 정보를 볼지 물음
                cout << endl;
                cout << "Do you want information on another room? enter 1. to exist is 0: ";
                cin >> datamore;
                if (datamore == 1) {
                    datamore = 0;
                }
                else {
                    return;
                }
            }
            
        }
        cout << endl;
        if (number == 0) { // 00~10호 까지 확인 후 더 볼것인가
            cout << "if you want more data enter 1. to exist is 0: ";
            cin >> datamore;
            if (datamore == 0) {
                cout << "thank you." << endl;
                return;
            }
            number += 1;
        }
        else {
            number = 0;
        }



    }

    //만들기
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