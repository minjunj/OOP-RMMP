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
ë£¸ë©?´?¸ ? ì²??? ?¨?
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while(true)
    {
        cout << "To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin  >> mateId;
        if(mateId == "0") // 0? ?? ¥ë°ì¼ë©? ì·¨ì
        {
            cout << "Quiting Register Roommate"<<endl;
            return;
        }
        /*
        ***? ì²??  ë£¸ë©?´?¸? ??´?ê°? ?°?´?°ë² ì´?¤? ì¡´ì¬?ì§? ???¤ë©? ?¤? ?ë¦?
        ?¬ê¸°ì ??¬ê°? ë°ì?  ? ??? ?´ mateIdë¥? "404 Not Founded : out of range"ë¡?
        ?? ¥ë°ì¼ë©? ë¬¸ì ê°? ?ê¸°ê¸° ?ë¬¸ì ?ì¤ì ê³ ì³ì¤ì¼?¨***
        */
        if(db.findOne("student",mateId,2)!=mateId)
        {
            cout << "Wrong input, enter again" << endl;
        }
        else // ë£¸ë© ??´?ë¥? ? ?? ¥?ë©?
        {
            roommateID = mateId;
            db.update("student",db.findOne("student",mateId,0),userID,8); //db? ë£¸ë©?´?¸? ë£¸ë©?´?¸ ??°?´?¸
            db.update("student",studentId,mateId,8);                      //db? ? ì²?? ë£¸ë©?´?¸ ??°?´?¸
            cout << "Now (" << userID << ") will be a roommate with (" << mateId <<") " <<endl;
        }
    }

    return;
}


//***·ë¸ÞÀÌÆ®¸¦ Ã£¾Æ³»´Â Æ¯Á¤ ¾Ë°í¸®ÁòÀÌ ÇÊ¿äÇÔ***
void Student::findRoommate(DataBase db)
{
    
    vector<string> main_survey;
    vector<vector<string>> roommate_survey= db.readSurvey();//surveyÀÇ Á¤º¸¸¦ ÀüºÎ ´ãÀº º¤ÅÍ
    vector<vector<string>> matchedRoommates;
    int applicantIndex=-1;//¸øÃ£¾ÒÀ»¶§ -1, Ã£¾ÒÀ»¶§´Â À§Ä¡ È®ÀÎ
    //»ç¿ëÀÚÀÇ À§Ä¡ È®ÀÎ
    for (size_t i = 0; i < roommate_survey.size(); i++) {
        if (roommate_survey[i][0] == "3su") //ÀÏ´ÜÀº ÀÓÀÇÀÇ °ªÀ» ³Ö¾îµÒ
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
    //·ë¸ÞÀÌÆ® ¸ÅÄª
    vector<pair<int,vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[0][j]) - stoi(roommate_survey[i][j]),2);
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //Á¡¼ö¸¦ ±âÁØÀ¸·Î Á¤·Ä (Á¡¼ö´Â °¢ ¹®Ç×º° Â÷ÀÌÀÇ Á¦°öÀÇ ÇÕ»ê)
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        cout << score.first << " ";
    }
    cout << endl;
    //Ãâ·Â
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
    //º¸¿ÏÇØ¾ßÇÒÁ¡. 1. »ó´ë¹æÀÌ ·ë¸ÞÀÌÆ® ÀÖ´ÂÁö ¿©ºÎ È®ÀÎÇØ¼­ »õ º¤ÅÍ¿¡ ´ã±â. 2. Ãâ·ÂµÇ´Â ³»¿ë¿¡ ÇÐ¹ø Æ÷ÇÔÇÏ±â 3. survey¶û student¶û ºñ±³´ëÁ¶ÇÏ´Â°Íµµ ÇÊ¿ä
    return;
}

/*
ë£¸ë©?´?¸ê°? ???ë§? ë°©ì ? ì²??  ? ?? ?¨?
*/
void Student::registerRoom(DataBase db)
{
    //ë£¸ë©?´?¸ê°? ??¼ë©? ë£¸ë©?´?¸ë¶??° êµ¬íê³? ?¤??¤?¼ê³? ë¦¬í´?¨
    if (roommateID.length()==0)
    {
        cout << "No roommate, register a roommate first" <<endl;
        return;
    }

    string regroomId; // ?? ¥ë°ì ? ì²?ë°? ë¬¸ì?´
    
    while(true)
    {
        cout << "Enter a Room to Register (Enter 0 to quit): ";
        cin  >> regroomId;
        // 0? ?? ¥ë°ì¼ë©? ì·¨ì
        if(regroomId == "0") 
        {
            cout << "Quiting Register Room"<<endl;
            return;
        }
        //?°?´?°ë² ì´?¤(room.txt)?? ì°¾ì?¨ isEmptyê°? true ì¦? ë¹ì´??? ? ì²?ê°??¥
        if(db.findOne("room",regroomId,2)=="true")
        {
            if(roomId.length()!=0) // ê¸°ì¡´? ì°¨ì???ê³? ?? ë°©ì´ ??¼ë©?
            {
                //***?? ê³? ë£¸ë©?´?¸? ? ì²? ë°©ì?? ""?¼ë¡? ì´ê¸°??ê³?***
                //***ê·? ë°©ì ? ë³´ë?? ì§???¼?¨***
            }
            roomId = regroomId; // ? ì²??? ë°? ë¬¸ì?´??? ?´ê±°ë¡ ë°ë??
            db.update("room",db.findOne("room",regroomId,0),"false",2); // ? ì²? ë°©ì isEmptyë¥? falseë¡? ë°ê¾¼?¤
            db.update("student",db.findOne("student",studentId,0),regroomId,6); // ? ì²? ??? ê¸°ì?¬ ë°©ì ë°ê¾¼?¤
            db.update("student",db.findOne("student",roommateID,0),regroomId,6); // ? ì²? ??? ë£¸ë©? ê¸°ì?¬ ë°©ì ë°ê¾¼?¤.
            cout << "Room successfully registered to ("<< roomId << ") with roommate ("<<roommateID <<") "<< endl; // ? ë³? ê³µì??
            return;
        }
        // ë°©ì´ ?´ë¯? ì°¨ì?¤ë©? ë£¨íë¥? ?¤? ?ë¦¬ê³  ?¤? ? ??  ? ??ë¡? ?´ì¤??¤
        else 
        {
            cout << "Room is already full " <<endl;
            cout << "Try another room" << endl;
        }
    }
    return;
}

/* 
???´ ì²ì ??ê°??/ë³?ê²½í  ?, ë£¸ë©?´?¸ ë§¤ì¹­? ?? ?¹?  ? ë³´ë¤? ?? ¥ ë°ë ?¨?
*/
void Student::insertInfo(DataBase db)
{
    cout << "Insert the default information of your life style" <<endl;
    cout << "To find the roommate matches with you" <<endl;
    vector<string> stuInfo; //??? ë³´ê?? ?´ê¸? ë²¡í°
    vector<string> questions {  "Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                "Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                "Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                "Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                "Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
                            }; // ?¸?? ë§ë  ì§ë¬¸ì§? ë²¡í°
    int checkNum; // ?? ¥ ? ?
    int idx = 0; // 0ë¶??° ì§ë¬¸ì§?? ?¬ê¸? ë§í¼ ì»¤ì§ ì»¤ì ?­? 
    while(idx != questions.size())
    {
        try{ // ?? ¥ë°ë ê³¼ì ?? ?¨ë¹¡ì´?¤?´ ? ?ê°? ???¼ ?¤ë¥¸ê±¸ ?? ¥ë°ë ??¬ê°? ë°ì ê°??¥
            cout << questions.at(idx);
            cin  >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // 1,2,3,4,5,6,7,8, ê¼?
            idx ++; // ?¤? ì§ë¬¸?¼ë¡?
        }
        catch(const exception& e) // ??¬ ??¸
        {
            cerr << e.what() << endl;
        }
    }

    //***stuInfoë¥? ?¤ë¸ì ?¸? ????¥?? ê³¼ì ?´ ??*** 
    // stuInfoê°? ????¥?  ? "1, 2, 3, 4" ì²ë¼ ,ê°? ?¤ê°?ë©´ì string??ë¡? ????¥?ê¸°ì ????¥??? string?¼ë¡í¨.

    stuInfo.pop_back();// ë§¨ë¤ , ? ê±?
    db.insertSurvey(stuInfo);
    //***stuInfoë¥? ?¤ë¸ì ?¸? ????¥?? ê³¼ì ?´ ??***
    

    return;
}

//ë¡ê·¸?? ëª??ë£?
void Student::logout()
{
    cout << "logging out"<<endl;
    return;
}


bool Student::isInfo()
{
    //***ë³´ì??***
    if(studentId.length()!=0) return true;
    else return false;
}

void Student::checkRoom(DataBase db)
{
    //ë§ë¤ê¸?
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