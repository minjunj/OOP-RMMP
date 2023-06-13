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
You can check the information of the current dormitory rooms
You can see more detailed information than students
Who lives in a particular room, etc
*/
void Admin::checkRoom(DataBase db) 
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
            cout << ">> Which zone do you want to see first.(g, i, s, t): "; //which area
            cin >> zone;
            cout << ">> Which floor do you want to see(2~6): "; //what floor
            cin >> floor;
            while(cin.fail()){
                cout << "** Wrong input try again"<<endl;
                cin.clear();
                cin.ignore(100 ,'\n');
                cout << ">> Which floor do you want to see(2~6): "; 
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
        if (db.findOne("room", numbers, 2) == "true") { //room is empty
            cout << " is empty!" << endl;
        }
        else if (db.findOne("room", numbers, 2) == "false") { //room isn't empty
            roommate = db.findOne("student", db.findOne("room", numbers, 0), 9);
            roommateid = roommate.replace(roommate.find("m"), 1, "s");
            cout << " was applied by " << db.findOne("student", db.findOne("room", numbers, 0), 1)
                << "," << db.findOne("student", roommateid, 1) << endl; // check who use room
        }
        numbers = "";


        count++;

        if (count % 10 == 0) { //Check the information of the room by 10 pieces.
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
Function to enter information on people who are unable to register as members, such as transfer students, into the database in advance 
or delete data
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
                //�����? ����. ������Ʈ�� �� nulló��
                db.Delete("student", db.findOne("student", studentcode, 0));

                cout << endl <<">> The student's information has been cleared." << endl <<endl;
            }
            else {
                return;
            }
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
function of increasing and decreasing rooms when situations occur, such as expanding and decreasing dormitories
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
            cout << ">> Which zone do you want to add first.(g, i, s, t): ";//which area
            cin>> zone;
            cout << ">> Which floor do you want to add (2~6): "; //what floor
            cin >> floor;
            int i = 1;
            string roomnumber = zone + to_string(floor * 100 + i);
            while (db.findOne("room", roomnumber, 1) == roomnumber) {
                 roomnumber = zone + to_string(floor * 100 + i);
                if (db.findOne("room", roomnumber, 1) != roomnumber) {//if room data is empty
                    cout << db.findOne("room", roomnumber, 1) << endl;
                    cout << "The addition room is " << roomnumber<<endl;
                    vector<unique_ptr<Room>> roomdata = db.room_JSON(roomnumber, true);
                    db.insert(roomdata, "room"); 
                    return;
                }
                i++;


            }
            return;

        }
        else if (selection == "2") {
            //delete room data
            string roomnumber;
            cout << "Which room do you want to delete (ex: g200): ";
            cin >> roomnumber;
            if (db.findOne("room", roomnumber, 1) != roomnumber) {
                cout << "Invalid input." << endl;
                return;
            }
            else{
                cout << "Do you want to erase " << roomnumber << "? (Y/N)"; //are you sure? delete room data?
                string check;
                cin >> check;
                string roomid = db.findOne("room", roomnumber, 0);
                if (check == "Y" || check == "y") {
                    db.Delete("room", roomid);
                    cout << "Room's information has been cleared about" <<roomnumber<< endl;
                }
                else {
                    cout << "** Quiting..." << endl;
                    return;
                }
                return;
            }
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
function that makes roommates and puts those who don't have roommates in the room
*/
void Admin::matchRoommates(DataBase db)
{
    vector<string> main_survey;
    vector<vector<string>> roommate_survey = db.readSurvey();//survey's data in here
    vector<vector<string>> matchedRoommates;
    vector<vector<string>> noRoommate;
    vector<string> rmmate;

    //matching roommate 
    vector<pair<int, vector<string>>> scores;

    for (size_t i = 0; i < roommate_survey.size(); i++) {
        int score = 0;
        for (size_t j = 1; j < roommate_survey[i].size(); j++) {
            score += pow(stoi(roommate_survey[i][j]), 2)*(10+j);//j is weight
        }
        scores.push_back(make_pair(score, roommate_survey[i]));
    }
    // Sort based on scores (scores are the sum of squares and weights for each question) A similar score waiting list based on this
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
    bool check = 0; //check has roommate
    for (const auto& roommate : matchedRoommates) {//Store sorted data separately for those who do not have a roommate
        if (db.findOne("student",  roommate[0], 8) == "404 Not Founded : out of range"
            || db.findOne("student", roommate[0], 8) == "") { // only if you don't have a roommate.
            noRoommate.push_back(roommate);
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }
    for (const auto& roommate : noRoommate) {//students who haven't roommate & Match based on aligned students' information
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

            db.update("student", studentid, roommateid9, 9); //update roommate data
            db.update("student", roommateid, studentid9, 9); 
            
            //The room is also automatically applied.
            i = 0;
            int room = 11;
            string roomid = to_string(room) + "r";
            //check where room is empty anything
            while (db.findOne("room", roomid, 2) !="true") {
                room += 1;
                roomid = to_string(room) + "r";
            }
            //cout << roomid << endl;

            db.update("room", db.findOne("room", roomid, 0), "false", 2);  //update room register
            db.update("student", db.findOne("student", studentid, 0), db.findOne("room", roomid, 0), 8); 
            db.update("student", db.findOne("student", roommateid, 0), db.findOne("room", roomid, 0), 8); 
            cout << ">> Room successfully registered to (" << db.findOne("student",rmmate[0],1) 
                << ") with roommate (" << db.findOne("student",roommate[0],1) << ") in " 
                <<db.findOne("room",roomid,1) <<". " << endl; // Information Description
            
        }
        //for (const auto& answer : roommate) {
        //    cout << answer << " ";
        //}
        //cout << endl;

    }
    return;
}
/*
function that initializes the entire dormitory by emptying it
*/
void Admin::cleanRoom(DataBase db) //Initialize the second column of room.txt to all true
{
    int i = 11;
    int count = 0;
    string s = to_string(i) + "r";

    while (db.findOne("room", to_string(i)+"r", 0) == to_string(i) + "r") {
        string s = to_string(i) + "r";
        //cout << s << db.findOne("room", to_string(i) + "r", 1) << endl;
        if (db.findOne("room", s, 2) == "false") { //who register room
            if (count == 0) {
                cout << ">> The rooms have been vacated." << endl;
            }


            db.update("room", s, "true", 2); //clear room
            string ss = db.findOne("student", s, 0);
            db.update("student", ss, "", 8); //clear student's room data
            string rs = db.findOne("student", s, 0);
            //cout << s<<ss << rs << endl;
            db.update("student", rs, "", 8);
            cout <<">> "<< db.findOne("room", s, 1) << " Room is empty. (" 
                <<db.findOne("student",ss,1) << ", " <<db.findOne("student",rs,1) << ")" << endl;
            count += 1;
        }
        i++;

    }

    if (count == 0) { //When there's no room to empty

        cout << ">> All rooms are empty." << endl;
    }
    return;
}

void Admin::checkStudents(DataBase db) 
{
    string choose;
    vector<vector<string>>student_data = db.readtxt("student");
    cout << ">> Choose the case you want" << endl;
    cout << ">>   1. Overall student information" << endl;
    cout << ">>   2. Information about specific students" << endl;
    cout << ">> Please enter a number. (exit 0): ";
    cin >> choose;
    cout << endl;

    if (choose == "1") {
        int i = 1;
        string check;
        for (const auto& student : student_data) {
            cout << ">> student ";
            for (const auto& data : student) {
                cout << data << ", ";
            }
            cout<<endl;
            if (i % 5 == 0) {
                cout << endl;
                cout << ">> Would you like to see more information? (Y/N) : ";
                cin >> check;
                cout << endl;
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
        cout << "no more student in here." << endl<<endl;
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
string Admin::getsurveyId() {return ""; }
string Admin::getUserName() { return ""; }
void Admin::releaseRoom(DataBase db) {return ;}