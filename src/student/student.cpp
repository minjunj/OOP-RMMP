#include "student.h"
#include <memory>
#include <algorithm>
#include <cmath>
using namespace std;

Student::Student(std::string stuId, int code, const std::string& userName, const std::string& userID, const std::string& userPW,  
             const std::string& class_, const std::string& room, 
            const bool gender, const std::string& mateID, const std::string& surveyId): User(userID, userPW, userName), studentId(stuId),
            studentCode(code),  gender(gender), roommateID(mateID), classOf(class_), roomId(room), surveyId(surveyId)
{
}

std::string Student::getFormattedData() const {
    std::string genderString = gender ? "Male" : "Female";
    return studentId + "," + std::to_string(studentCode) + "," + userName + "," + userID + ","
        + userPW + "," + classOf + "," + genderString + "," + role + "," + roomId + "," + roommateID + "," + surveyId;

}
/*
Request Roommate Function
*/
void Student::registerRoommate(DataBase db)
{
    string mateId;

    while (true)
    {
        if(roommateID != "")
        {
            cout <<"** You already have a roommate, to register again cancel the rommate first\n" << endl;
            break;
        }
        cout << ">> To register a roommate, Enter the person's studentID(ex: 2022xxxx) , to exit enter 0 : ";
        cin >> mateId;
        string gen;
        if (gender) gen = "Male";
        else  gen = "Female";
        if (mateId == "0") // Cancel when 0 is entered
        {
            cout << "** Quiting Register Roommate" << endl;
            return;
        }

        if (db.findOne("student", mateId, 1) != mateId)
        {
            cout << "\n** Wrong input, try again" << endl;
        }
        else if(db.findOne("student", mateId, 6)==gen)// If the gender is the same
        {
            if(db.findOne("student", mateId, 9) == "404 Not Founded : out of range")
            {
                roommateID = db.findOne("student", mateId, 0);
                cout << studentId << "  " << roommateID<<endl; 
                string studentIDrm= studentId.replace(studentId.find("s"), 1, "m");
                string roommateIDrm= roommateID.replace(roommateID.find("s"), 1, "m");
                cout << studentIDrm <<" " << roommateIDrm <<endl;
                db.update("student", db.findOne("student", mateId, 0), studentIDrm, 9); //Update roommate's roommate on db
                db.update("student", db.findOne("student", to_string(studentCode), 0),roommateIDrm, 9); //Update applicant roommate on db
                cout << ">> Now (" <<to_string(studentCode) << ") will be a roommate with (" << mateId << ") " << endl;
                break;
            }
            else
            {
                cout << "** Following student "<< mateId <<" has already a roommate "<< endl;
            }

        }
        else
        {
            cout << "** Wrong gender student, try again" << endl;
        }
    }

    return;
}
/*
Functions to release roommates
*/
void Student::releaseRoommate(DataBase db)
{
    string mateid;
    mateid = db.findOne("student", studentId, 9);
    if (db.findOne("student", studentId, 9) == "404 Not Founded : out of range") { // If you don't have a roommate
        cout << "You don't have roommate!" << endl;
        return;
    }
    string roomid= db.findOne("student", studentId, 8);
    mateid = mateid.replace(mateid.find("m"), 1, "s");
    cout << "Your roommate is " << db.findOne("student", mateid, 1)
        <<" " << db.findOne("student", mateid, 2)  << endl;
    if (roomid != "404 Not Founded : out of range") { //If the room is not empty
        cout << "WARNING: Your room ("<< db.findOne("room",roomid,1)
            <<") will automatically be checked out when you release your roommate." << endl;
    }
    cout << "Are you sure you want to release your roommate? (Y/N): ";
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y") {
        db.update("room", roomid, "true", 2);
        db.update("student", studentId, "", 9);
        db.update("student", mateid, "", 9);
        if (roomid != "404 Not Founded : out of range") {
            db.update("student", studentId, "", 8);
            db.update("student", mateid, "", 8);
        }

    }
    else {
        return;
    }

    return;
}

string Student::getsurveyId()
{
    return surveyId;
}
//***Requires a specific algorithm to find roommates*** + Male and female classification, 3 people who have not applied for roommates
void Student::findRoommate(DataBase db)
{
    vector<string> main_survey;
    vector<vector<string>> roommate_survey= db.readSurvey();//survey's full information vector
    vector<vector<string>> matchedRoommates;
    int applicantIndex=-1;//when not found -1, check the location when found
    //Check the user's location
    for (size_t i = 0; i < roommate_survey.size(); i++) {
        if (roommate_survey[i][0] == db.findOne("student", studentId, 10)) 
            applicantIndex = i;
    }
    if (applicantIndex != -1) {
        vector<string> applicant_survey = roommate_survey[applicantIndex];
        roommate_survey.erase(roommate_survey.begin() + applicantIndex);
        roommate_survey.insert(roommate_survey.begin(), applicant_survey);
    }
    else {
        cout << "** Please enter your information first.\n" << endl;
    }
    //Matching roommates
    vector<pair<int,vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[0][j]) - stoi(roommate_survey[i][j]),2)*j;
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    // Sort based on scores (scores are the sum of the squares of the differences for each item)
    sort(scores.begin(), scores.end());
    cout << "\n>> ";
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        cout << score.first << " ";
    }
    cout << endl;
    //output
    cout << ">> Matched roommates:" <<endl;
    int i = 0;
    int index = 0;
    bool check = 0; //To check if there is a roommate
    for (const auto& roommate : matchedRoommates) {
        if (i == 0) {
            cout << endl;
            cout << ">> your info : " ;
        }
        else {
            cout << ">> Answer " << i << ": ";
            cout << db.findOne("student", roommate[0], 1); //graduates.rommate[0] is a unique identification number, such as 1su
            // cout << db.findOne("student", db.findOne("student", roommate[0], 1), 8);
            if (db.findOne("student", roommate[0], 9) == "404 Not Founded : out of range") { //does student have a roommate.
                cout << " has no roommate" << endl; //// set to output only when there is no roommate
                check = 0;
            }
            else {
                check = 1;
                cout << " has roommate" << endl;//?—¬ê¸°ì„œ ?›?ž˜?¼ë©? continueë¡? ?Œ?•„ê°?ê²? ?• ?“¯
            }
            cout << ">> roommate candidate info: ";
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
            cout << ">> The most appropriate order of roommates." << endl;
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
A function that allows you to request a room only when you have a roommate
*/
void Student::registerRoom(DataBase db)
{
    //If you don't have a roommate, return to find a roommate and come back
    if (roommateID.length() == 0)
    {
        cout << "** No roommate, register a roommate first" << endl;
        return;
    }

    string regroomId; // Application room string to be entered
    while (true)
    {
        cout << ">> Enter a Room to Register (Enter 0 to quit): ";
        cin >> regroomId; //like g217
        // Cancel when 0 is entered
        if (regroomId == "0")
        {
            cout << "** Quiting Register Room" << endl;
            return;
        }
        //Apply when isEmpty found in the database (room.txt) is true, that is, empty
        if (db.findOne("room", regroomId, 2) == "true")
        {
            if (roomId.length() != 0) //  If you have a previously occupied room
            {
                db.update("room", db.findOne("room", roomId, 0), "true", 2); // change the isEmpty in the room to true
                db.update("student", db.findOne("student", studentId, 0), "", 8); 
                db.update("student", db.findOne("student", roommateID, 0), "", 8); 
            }
            roomId = regroomId; 
            db.update("room", db.findOne("room", regroomId, 0), "false", 2); // change the isEmpty in the application room to false
            db.update("student", db.findOne("student", studentId, 0), db.findOne("room", regroomId, 0), 8); // change the dormitory room of the applicant
            db.update("student", db.findOne("student", roommateID, 0), db.findOne("room", regroomId, 0), 8); // change the room of the applicant's roommate.
            cout << ">> Room successfully registered to (" << roomId << ") with roommate (" << roommateID << ") " << endl; // Information Description
            return;
        }
        // If the room is already full, it will allow you to turn the loop back and select again
        else
        {
            cout << "** Room is already full " << endl;
            cout << "** Try another room" << endl;
        }
    }
    return;
}

/*
A function that receives specific information for roommate matching when a student first signs up/changes a member
*/
void Student::insertInfo(DataBase db)
{
    cout << ">> Insert the default information of your life style" << endl;
    cout << ">> To find the roommate matches with you" << endl;
    vector<string> stuInfo; //Vector containing student information
    vector<string> questions{ ">> Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                ">> Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                ">> Enter your prefering airconditioning temperature (1: ~~ 2: ~~ 3: ~~ 4: ~~) : " ,
                                ">> Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                ">> Enter if you snore (1: Every night 2: Sometimes 3: Never 4: ~~)"
    }; // Questionnaire made for convenience Vector bedtime, wake-up time, and do you get hot easily, alcohol, cigarettes and snoring?
    int checkNum; //  input integer
    int idx = 0; // // The role of a cursor that will grow from zero to the size of the questionnaire


    while (idx != questions.size())
    {
        try { // In the process of receiving input, there may be an error in which the sticky faces receive something other than an integer
            cout << questions.at(idx);
            cin >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // like 1,2,3,4,5,6,7,8,
            idx++; // Next question
        }
        catch (const exception& e) // error check
        {
            cerr << e.what() << endl;
        }
    }

    //***StuInfo needs to be saved to an object***
    // When stuInfo is stored, it is stored as a string as it enters, such as "1, 2, 3, 4", so the storage is called string.
    
    stuInfo.pop_back();// at the back, remove
    db.insertSurvey(stuInfo);
    //***StuInfo needs to be saved to an object***
    return;
}




bool Student::isInfo()
{
    //requires confirmation that information has been entered. Check if there is a 'su' when you type survey
    if (studentId=="0") {//surveyid needs to be checked for containment Need modification
    }
    return true;
 
}

void Student::checkRoom(DataBase db) //Check Room Status Output
{
 int datamore = 0;
    string numbers;
    int number=0;
    string zone;
    int floor;
    int count = 0;

    while (true) {
        if (count == 0) {
            cout << "Which zone do you want to see first.(g, i, s, t): "; //which district
            cin >> zone;
            cout << "Which floor do you want to see(2~6): "; //what floor is it
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
        if (db.findOne("room", numbers, 2) == "true") { //if the room is empty
            cout << " is empty!" << endl;
        }
        else if (db.findOne("room", numbers, 2) == "false") { //if the room is not empty
            cout << " was applied." << endl;
        }
        numbers = "";


        count++;
        if (count % 10 == 0) { //Will you cut it into 10 pieces to see more
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
