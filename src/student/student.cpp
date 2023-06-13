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
        if (mateId == "0") //when 0 is entered. cancel
        {
            cout << "** Quiting Register Roommate" << endl;
            return;
        }
 
        if (db.findOne("student", mateId, 1) != mateId)
        {
            cout << "\n** Wrong input, try again" << endl;
        }
        else if(db.findOne("student", mateId, 6)==gen)// check gender
        {
            if(db.findOne("student", mateId, 9) == "404 Not Founded : out of range")
            {
                roommateID = db.findOne("student", mateId, 0);
                string studentid = studentId;
                cout << studentId << "  " << roommateID<<endl; 
                string studentIDrm= studentid.replace(studentid.find("s"), 1, "m");
                string roommateIDrm= roommateID.replace(roommateID.find("s"), 1, "m");
                //cout << studentIDrm <<" " << roommateIDrm <<endl;
                db.update("student", db.findOne("student", mateId, 0), studentIDrm, 9); //roommate update
                db.update("student", db.findOne("student", to_string(studentCode), 0),roommateIDrm, 9); 
                cout << ">> Now (" <<to_string(studentCode) << ") will be a roommate with (" << mateId << ") " << endl;
                roommateID = roommateIDrm;
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
Release Roommate function
*/
void Student::releaseRoommate(DataBase db)
{
    string mateid;
    mateid = roommateID;
    if (db.findOne("student", studentId, 9) == "404 Not Founded : out of range") { //if student's doesn't have roommate
        cout << "** You don't have roommate!" << endl;
        return;
    }
    mateid = mateid.replace(mateid.find("m"), 1, "s");
    cout << ">> Your roommate is " << db.findOne("student", mateid, 1)
        <<" " << db.findOne("student", mateid, 2)  << endl;
    if (roomId != "") { //if room isn't empty
        cout << ">> WARNING: Your room ("<< db.findOne("room",roomId,1)
            <<") will automatically be checked out when you release your roommate." << endl;
    }
    cout << ">> Are you sure you want to release your roommate? (Y/N): ";
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y") {
        db.update("student", studentId, "", 9);
        db.update("student", mateid, "", 9);

        if (roomId != "") {
            db.update("room", db.findOne("room", roomId, 0), "true", 2);
            db.update("student", studentId, "", 8);
            db.update("student", mateid, "", 8);
            roomId = "";
        }
        roommateID = "";
        cout <<">> Successfully released "<<endl;
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
// find roommate data
void Student::findRoommate(DataBase db)
{
    vector<string> main_survey;
    vector<vector<string>> roommate_survey= db.readSurvey();//a vector containing data from a survey
    vector<vector<string>> matchedRoommates;
    vector<vector<string>> noRoommate;
    int applicantIndex=-1;//Return -1 when not found, check location when found
    //check student's survey
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
    //matching roommate
    vector<pair<int,vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[0][j]) - stoi(roommate_survey[i][j]),2)*(10+j);
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    //sort of score(score is a value that is weighted to the square of the difference in the answer)
    //cout << "\n>> ";
    sort(scores.begin(), scores.end());
    for (const auto& score : scores) {
        matchedRoommates.push_back(score.second);
        //cout << score.first << " ";
    }
    cout << endl;
    //output
    cout << ">> Matched roommates:" << endl;
    int i = 0;
    int index = 0;
    string genderString = gender ? "Male" : "Female";
    for (const auto& roommate : matchedRoommates) {//Separate data to match conditions
        if (genderString == db.findOne("student", roommate[0], 6)) {//same gender
            if (db.findOne("student", roommate[0], 9) == "404 Not Founded : out of range"
                || db.findOne("student", roommate[0], 9) == "") { //don't have roommate
                noRoommate.push_back(roommate);
            }

        }

    }
    for (const auto& roommate : noRoommate) {
        if (i == 0) {
            cout << endl;
            cout << ">> your info : ";
        }
        else {
            cout << ">> Answer " << i << ": ";
            cout << db.findOne("student", roommate[0], 1); 
            cout << " has no roommate" << endl; 
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
    if (i == 0) { // If no student meets the requirements
        cout << ">>No roommate targets."<<endl;
    }
    cout << endl;
    return;
}
/*
function that allows you to request a room only when you have a roommate
*/
void Student::registerRoom(DataBase db)
{
    //cout << roommateID  <<endl;
                  
    //if you don't have roommate. apply for a roommate first
    if (roommateID.length() == 0)
    {
        cout << "** No roommate, register a roommate first" << endl;
        return;
    }

    string regroomId; // Room information to apply for

    while (true)
    {
        cout << ">> Enter a Room to Register (Enter 0 to quit): ";
        cin >> regroomId; //like g200
        // if enter 0. cancel
        string roommateId = roommateID;
        roommateId = roommateId.replace(roommateId.find("m"), 1, "s");
        if (regroomId == "0")
        {
            cout << "** Quiting Register Room" << endl;
            return;
        }
        //in Database(room.txt). when isempty==true. can apply
        if (db.findOne("room", regroomId, 2) == "true")
        {
            if (roomId.length() != 0) // If you've already signed up for a room
            {
                db.update("room", roomId, "true", 2); 
                db.update("student", studentId, "", 8); 
                db.update("student", roommateId, "", 8); 
                //*Initialize the information in the requested room.
            }
            roomId = db.findOne("room", regroomId, 0); // Information about the room you want to apply
            db.update("room", db.findOne("room", regroomId, 0), "false", 2); // change the isEmpty in the application room to false
            db.update("student", studentId, roomId, 8); // change the dormitory room of the applicant
            db.update("student", roommateId, roomId, 8); // change the room of the applicant's roommate.
            cout << ">> Room successfully registered to (" << roomId << ") with roommate (" << roommateID << ") " << endl; 
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
function to release the requested room
*/
void Student::releaseRoom(DataBase db)
{
    if (roomId == "404 Not Founded : out of range") { //if don't register room
        cout << "You didn't apply for a room!" << endl;
        return;
    }
    string mateid;
    mateid = roommateID;
    mateid = mateid.replace(mateid.find("m"), 1, "s");
    cout << "Your roomm is " << roomId << endl;
    cout << "Are you sure you want to release your room (" << roomId <<") ? (Y / N) : ";
    string answer;
    cin >> answer;
    if (answer == "y" || answer == "Y") {
        cout << mateid << " " << studentId <<endl;
        db.update("room", db.findOne("room", roomId, 0), "true", 2);
        db.update("student", studentId, "", 8);
        db.update("student", mateid, "", 8);
        roomId = "";
    }
    else {
        return;
    }

    return;
}
/*
Functions that receive student information
*/
void Student::insertInfo(DataBase db)
{
    cout << ">> Insert the default information of your life style" << endl;
    cout << ">> To find the roommate matches with you" << endl;
    vector<string> stuInfo; //student's survey vector
    vector<string> questions{ ">> Enter your sleeping time (1: earlier than 10p.m. 2: 10p.m ~ 12a.m. 3: 12a.m. ~ 2a.m. 4. later than 2a.m) : ",
                                ">> Enter your awaking time (1: earlier that 6a.m. 2: 6a.m. ~ 8a.m. 3: 8a.m. ~ 10a.m. 4: later than 10a.m.) : ",
                                ">> Enter cleaning frequency (1: at least once a day 2: 3-4 times a week 3: once a week 4: once a month) : ",
                                ">> Enter how often you want to deliveries (1: at least once a day 2: 3-4 times a week 3: once a week 4: once a month) : ",
                                ">> Enter your studnet number (1: 23 2: 22 3: 21 4: 20 or less) : ",
                                ">> Enter your frequency of drinking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                ">> Enter your frequency of smoking (1: Always 2: Often 3: Sometimes 4: Never) : ",
                                ">> Enter if you snore (1: Every night 2: Sometimes 3: Only when I'm stressed 4: Never) : "
    }; 
    int checkNum; //input integer
    int idx = 0; // The integer of growing larger by the amount of questions from zero

    while (idx != questions.size())
    {
        try { // When a non-integer value is entered
            cout << questions.at(idx);
            cin >> checkNum;
            stuInfo.push_back(to_string(checkNum));
            stuInfo.push_back(","); // like 1,4,3,2,1,1,2
            idx++; //next question
        }
        catch (const exception& e) // check error
        {
            cerr << e.what() << endl;
        }
    }

    //***save stuInfo to survey.txt
    if (surveyId != "NULL")
        db.Delete("survey",surveyId);
    surveyId = db.insertSurvey(stuInfo);
    db.update("student", studentId, surveyId, 10);
    
    return;
}




bool Student::isInfo()
{
    if (studentId=="0") {
        return false;
    }
    return true;
 
}

void Student::checkRoom(DataBase db) //Function to check the room status of the room
{
    int datamore = 0;
    string numbers;
    int number=0;
    string zone;
    int floor;
    int count = 0;

    while (true) {
        if (count == 0) {
            cout << ">> Which zone do you want to see first.(g, i, s, t): "; //which area
            cin >> zone;
            cout << ">> Which floor do you want to see(2~6): "; //what floor
            cin >> floor;
            while(cin.fail()){
                cout << "** Wrong input try again"<<endl;
                cin.clear();
                cin.ignore(100 ,'\n');
                cout << ">> Which floor do you want to see(2~6): "; 
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
        if (db.findOne("room", numbers, 2) == "true") { //room is empty
            cout << " is empty!" << endl;
        }
        else if (db.findOne("room", numbers, 2) == "false") { //room isn't empty
            cout << " was applied." << endl;
        }
        numbers = "";

        count++;
        if (count % 10 == 0) { //Check the information of the room by 10 pieces.
            cout << ">> if you want more data enter 1. to exist is 0: ";
            cin >> datamore;
            cout << endl;
            if (datamore == 0) {
                cout << ">> thank you." << endl;
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
