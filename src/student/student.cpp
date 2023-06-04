#include "student.h"
#include <memory>

using namespace std;

Student::Student(std::string stuId, int code, const std::string& userName, const std::string& userID, const std::string& userPW,  
             const std::string& class_, const std::string& room, 
            const bool gender, const std::string& mateID): User(userID, userPW, userName), studentId(stuId),
            studentCode(code),  gender(gender), roommateID(mateID), classOf(class_), roomId(room)

{
}

std::string Student::getFormattedData() const {
    std::string genderString = gender ? "Male" : "Female";
    return studentId + "," + std::to_string(studentCode) + "," + userName + "," + userID + ","
        + userPW + "," + classOf + "," + genderString + "," + role + "," + roomId + "," + roommateID;

}
/*
룸메?��?�� ?���??��?�� ?��?��
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while(true)
    {
        cout << "To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin  >> mateId;
        if(mateId == "0") // 0?�� ?��?��받으�? 취소
        {
            cout << "Quiting Register Roommate"<<endl;
            return;
        }
        /*
        ***?���??�� 룸메?��?��?�� ?��?��?���? ?��?��?��베이?��?�� 존재?���? ?��?��?���? ?��?�� ?���?
        ?��기서 ?��?���? 발생?�� ?�� ?��?��?��?�� mateId�? "404 Not Founded : out of range"�?
        ?��?��받으�? 문제�? ?��기기 ?��문에 ?��중에 고쳐줘야?��***
        */
        if(db.findOne("student",mateId,2)!=mateId)
        {
            cout << "Wrong input, enter again" << endl;
        }
        else // 룸메 ?��?��?���? ?�� ?��?��?���?
        {
            roommateID = mateId;
            db.update("student",db.findOne("student",mateId,0),userID,8); //db?�� 룸메?��?��?�� 룸메?��?�� ?��?��?��?��
            db.update("student",studentId,mateId,8);                      //db?�� ?���??�� 룸메?��?�� ?��?��?��?��
            cout << "Now (" << userID << ") will be a roommate with (" << mateId <<") " <<endl;
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
룸메?��?���? ?��?��?���? 방을 ?���??�� ?�� ?��?�� ?��?��
*/
void Student::registerRoom(DataBase db)
{
    //룸메?��?���? ?��?���? 룸메?��?���??�� 구하�? ?��?��?��?���? 리턴?��
    if (roommateID.length()==0)
    {
        cout << "No roommate, register a roommate first" <<endl;
        return;
    }

    string regroomId; // ?��?��받을 ?���?�? 문자?��
    
    while(true)
    {
        cout << "Enter a Room to Register (Enter 0 to quit): ";
        cin  >> regroomId;
        // 0?�� ?��?��받으�? 취소
        if(regroomId == "0") 
        {
            cout << "Quiting Register Room"<<endl;
            return;
        }
        //?��?��?��베이?��(room.txt)?��?�� 찾아?�� isEmpty�? true �? 비어?��?��?�� ?���?�??��
        if(db.findOne("room",regroomId,2)=="true")
        {
            if(roomId.length()!=0) // 기존?�� 차�???���? ?��?�� 방이 ?��?���?
            {
                //***?��?���? 룸메?��?��?�� ?���? 방�?? ""?���? 초기?��?���?***
                //***�? 방의 ?��보�?? �??��?��?��***
            }
            roomId = regroomId; // ?���??��?�� �? 문자?��??? ?��거로 바�??
            db.update("room",db.findOne("room",regroomId,0),"false",2); // ?���? 방의 isEmpty�? false�? 바꾼?��
            db.update("student",db.findOne("student",studentId,0),regroomId,6); // ?���? ?��?��?�� 기숙?�� 방을 바꾼?��
            db.update("student",db.findOne("student",roommateID,0),regroomId,6); // ?���? ?��?��?�� 룸메?�� 기숙?�� 방을 바꾼?��.
            cout << "Room successfully registered to ("<< roomId << ") with roommate ("<<roommateID <<") "<< endl; // ?���? 공�??
            return;
        }
        // 방이 ?���? 차있?���? 루프�? ?��?�� ?��리고 ?��?�� ?��?��?�� ?�� ?��?���? ?���??��
        else 
        {
            cout << "Room is already full " <<endl;
            cout << "Try another room" << endl;
        }
    }
    return;
}

/* 
?��?��?�� 처음 ?��?���??��/�?경할 ?��, 룸메?��?�� 매칭?�� ?��?�� ?��?�� ?��보들?�� ?��?�� 받는 ?��?��
*/
void Student::insertInfo(DataBase db)
{
    cout << "Insert the default information of your life style" <<endl;
    cout << "To find the roommate matches with you" <<endl;
    vector<string> stuInfo; //?��?��?��보�?? ?���? 벡터
    vector<string> questions {  "Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                "Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                "Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                "Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                "Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
                            }; // ?��?��?�� 만든 질문�? 벡터
    int checkNum; // ?��?�� ?��?��
    int idx = 0; // 0�??�� 질문�??�� ?���? 만큼 커질 커서 ?��?��
    while(idx != questions.size())
    {
        try{ // ?��?��받는 과정?��?�� ?��빡이?��?�� ?��?���? ?��?��?�� ?��른걸 ?��?��받는 ?��?���? 발생 �??��
            cout << questions.at(idx);
            cin  >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // 1,2,3,4,5,6,7,8, �?
            idx ++; // ?��?�� 질문?���?
        }
        catch(const exception& e) // ?��?�� ?��?��
        {
            cerr << e.what() << endl;
        }
    }

    //***stuInfo�? ?��브젝?��?�� ????��?��?�� 과정?�� ?��?��*** 
    // stuInfo�? ????��?�� ?�� "1, 2, 3, 4" 처럼 ,�? ?���?면서 string?��?���? ????��?��기에 ????��??? string?��로함.

    stuInfo.pop_back();// 맨뒤 , ?���?
    db.insertSurvey(stuInfo);
    //***stuInfo�? ?��브젝?��?�� ????��?��?�� 과정?�� ?��?��***
    

    return;
}

//로그?��?�� �??�?
void Student::logout()
{
    cout << "logging out"<<endl;
    return;
}


bool Student::isInfo()
{
    //***보완?��?��***
    if(studentId.length()!=0) return true;
    else return false;
}

void Student::checkRoom(DataBase db)
{
    //만들�?
    return;
}

string Student::getUserName()
{
    return userName;
}


void Student::addDelStudents(DataBase db){return;}
void Student::addDelRoom(DataBase db){return;}
void Student::matchRoommates(DataBase db){return;}
void Student::cleanRoom(DataBase db){return;}
void Student::printInfo(){return;}
void Student::checkStudents(DataBase db){return;}