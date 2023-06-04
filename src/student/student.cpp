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
ë£¸ë©”?´?Š¸ ?‹ ì²??•˜?Š” ?•¨?ˆ˜
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while(true)
    {
        cout << "To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin  >> mateId;
        if(mateId == "0") // 0?„ ?…? ¥ë°›ìœ¼ë©? ì·¨ì†Œ
        {
            cout << "Quiting Register Roommate"<<endl;
            return;
        }
        /*
        ***?‹ ì²??•  ë£¸ë©”?´?Š¸?˜ ?•„?´?””ê°? ?°?´?„°ë² ì´?Š¤?— ì¡´ì¬?•˜ì§? ?•Š?Š”?‹¤ë©? ?‹¤?‹œ ?Œë¦?
        ?—¬ê¸°ì„œ ?—?Ÿ¬ê°? ë°œìƒ?•  ?ˆ˜ ?ˆ?Š”? ?´ mateIdë¥? "404 Not Founded : out of range"ë¡?
        ?…? ¥ë°›ìœ¼ë©? ë¬¸ì œê°? ?ƒê¸°ê¸° ?•Œë¬¸ì— ?‚˜ì¤‘ì— ê³ ì³ì¤˜ì•¼?•¨***
        */
        if(db.findOne("student",mateId,2)!=mateId)
        {
            cout << "Wrong input, enter again" << endl;
        }
        else // ë£¸ë©” ?•„?´?””ë¥? ?˜ ?…? ¥?•˜ë©?
        {
            roommateID = mateId;
            db.update("student",db.findOne("student",mateId,0),userID,8); //db?— ë£¸ë©”?´?Š¸?˜ ë£¸ë©”?´?Š¸ ?—…?°?´?Š¸
            db.update("student",studentId,mateId,8);                      //db?— ?‹ ì²?? ë£¸ë©”?´?Š¸ ?—…?°?´?Š¸
            cout << "Now (" << userID << ") will be a roommate with (" << mateId <<") " <<endl;
        }
    }

    return;
}


//***·ë¸ŞÀÌÆ®¸¦ Ã£¾Æ³»´Â Æ¯Á¤ ¾Ë°í¸®ÁòÀÌ ÇÊ¿äÇÔ***
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
    //·ë¸ŞÀÌÆ® ¸ÅÄª
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
    //º¸¿ÏÇØ¾ßÇÒÁ¡. 1. »ó´ë¹æÀÌ ·ë¸ŞÀÌÆ® ÀÖ´ÂÁö ¿©ºÎ È®ÀÎÇØ¼­ »õ º¤ÅÍ¿¡ ´ã±â. 2. Ãâ·ÂµÇ´Â ³»¿ë¿¡ ÇĞ¹ø Æ÷ÇÔÇÏ±â 3. survey¶û student¶û ºñ±³´ëÁ¶ÇÏ´Â°Íµµ ÇÊ¿ä
    return;
}

/*
ë£¸ë©”?´?Š¸ê°? ?ˆ?„?•Œë§? ë°©ì„ ?‹ ì²??•  ?ˆ˜ ?ˆ?Š” ?•¨?ˆ˜
*/
void Student::registerRoom(DataBase db)
{
    //ë£¸ë©”?´?Š¸ê°? ?—†?œ¼ë©? ë£¸ë©”?´?Š¸ë¶??„° êµ¬í•˜ê³? ?‹¤?‹œ?˜¤?¼ê³? ë¦¬í„´?•¨
    if (roommateID.length()==0)
    {
        cout << "No roommate, register a roommate first" <<endl;
        return;
    }

    string regroomId; // ?…? ¥ë°›ì„ ?‹ ì²?ë°? ë¬¸ì?—´
    
    while(true)
    {
        cout << "Enter a Room to Register (Enter 0 to quit): ";
        cin  >> regroomId;
        // 0?„ ?…? ¥ë°›ìœ¼ë©? ì·¨ì†Œ
        if(regroomId == "0") 
        {
            cout << "Quiting Register Room"<<endl;
            return;
        }
        //?°?´?„°ë² ì´?Š¤(room.txt)?—?„œ ì°¾ì•„?˜¨ isEmptyê°? true ì¦? ë¹„ì–´?ˆ?„?•Œ ?‹ ì²?ê°??Š¥
        if(db.findOne("room",regroomId,2)=="true")
        {
            if(roomId.length()!=0) // ê¸°ì¡´?— ì°¨ì???•˜ê³? ?ˆ?˜ ë°©ì´ ?ˆ?œ¼ë©?
            {
                //***??‹ ê³? ë£¸ë©”?´?Š¸?˜ ?‹ ì²? ë°©ì?? ""?œ¼ë¡? ì´ˆê¸°?™”?•˜ê³?***
                //***ê·? ë°©ì˜ ? •ë³´ë?? ì§??›Œ?•¼?•¨***
            }
            roomId = regroomId; // ?‹ ì²???˜ ë°? ë¬¸ì?—´??? ?´ê±°ë¡œ ë°”ë??
            db.update("room",db.findOne("room",regroomId,0),"false",2); // ?‹ ì²? ë°©ì˜ isEmptyë¥? falseë¡? ë°”ê¾¼?‹¤
            db.update("student",db.findOne("student",studentId,0),regroomId,6); // ?‹ ì²? ?•™?ƒ?˜ ê¸°ìˆ™?‚¬ ë°©ì„ ë°”ê¾¼?‹¤
            db.update("student",db.findOne("student",roommateID,0),regroomId,6); // ?‹ ì²? ?•™?ƒ?˜ ë£¸ë©”?˜ ê¸°ìˆ™?‚¬ ë°©ì„ ë°”ê¾¼?‹¤.
            cout << "Room successfully registered to ("<< roomId << ") with roommate ("<<roommateID <<") "<< endl; // ? •ë³? ê³µì??
            return;
        }
        // ë°©ì´ ?´ë¯? ì°¨ìˆ?‹¤ë©? ë£¨í”„ë¥? ?‹¤?‹œ ?Œë¦¬ê³  ?‹¤?‹œ ?„ ?ƒ?•  ?ˆ˜ ?ˆ?„ë¡? ?•´ì¤??‹¤
        else 
        {
            cout << "Room is already full " <<endl;
            cout << "Try another room" << endl;
        }
    }
    return;
}

/* 
?•™?ƒ?´ ì²˜ìŒ ?šŒ?›ê°??…/ë³?ê²½í•  ?•Œ, ë£¸ë©”?´?Š¸ ë§¤ì¹­?„ ?œ„?•œ ?Š¹? • ? •ë³´ë“¤?„ ?…? ¥ ë°›ëŠ” ?•¨?ˆ˜
*/
void Student::insertInfo(DataBase db)
{
    cout << "Insert the default information of your life style" <<endl;
    cout << "To find the roommate matches with you" <<endl;
    vector<string> stuInfo; //?•™?ƒ? •ë³´ê?? ?‹´ê¸? ë²¡í„°
    vector<string> questions {  "Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                "Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                "Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                "Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                "Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
                            }; // ?¸?˜?ƒ ë§Œë“  ì§ˆë¬¸ì§? ë²¡í„°
    int checkNum; // ?…? ¥ ? •?ˆ˜
    int idx = 0; // 0ë¶??„° ì§ˆë¬¸ì§??˜ ?¬ê¸? ë§Œí¼ ì»¤ì§ˆ ì»¤ì„œ ?—­?• 
    while(idx != questions.size())
    {
        try{ // ?…? ¥ë°›ëŠ” ê³¼ì •?—?„œ ?¨ë¹¡ì´?“¤?´ ? •?ˆ˜ê°? ?•„?‹ˆ?¼ ?‹¤ë¥¸ê±¸ ?…? ¥ë°›ëŠ” ?—?Ÿ¬ê°? ë°œìƒ ê°??Š¥
            cout << questions.at(idx);
            cin  >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // 1,2,3,4,5,6,7,8, ê¼?
            idx ++; // ?‹¤?Œ ì§ˆë¬¸?œ¼ë¡?
        }
        catch(const exception& e) // ?—?Ÿ¬ ?™•?¸
        {
            cerr << e.what() << endl;
        }
    }

    //***stuInfoë¥? ?˜¤ë¸Œì ?Š¸?— ????¥?•˜?Š” ê³¼ì •?´ ?•„?š”*** 
    // stuInfoê°? ????¥?  ?–ˆ "1, 2, 3, 4" ì²˜ëŸ¼ ,ê°? ?“¤ê°?ë©´ì„œ string?˜•?ƒœë¡? ????¥?˜ê¸°ì— ????¥??? string?œ¼ë¡œí•¨.

    stuInfo.pop_back();// ë§¨ë’¤ , ? œê±?
    db.insertSurvey(stuInfo);
    //***stuInfoë¥? ?˜¤ë¸Œì ?Š¸?— ????¥?•˜?Š” ê³¼ì •?´ ?•„?š”***
    

    return;
}

//ë¡œê·¸?•„?›ƒ ëª??ë£?
void Student::logout()
{
    cout << "logging out"<<endl;
    return;
}


bool Student::isInfo()
{
    //***ë³´ì™„?•„?š”***
    if(studentId.length()!=0) return true;
    else return false;
}

void Student::checkRoom(DataBase db)
{
    //ë§Œë“¤ê¸?
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