// database.cpp
#include "DataBase.h"
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"
#include <typeinfo>
#include <memory>
#include <numeric>

#include <algorithm>
#include <sstream>
int count_room = 0;
int count_student = 0;
int count_survey = 0;
int count_admin = 0;
class NotFoundedDataBaseException {

};

class NotFoundedException {

};

template <typename T>
void DataBase::insert(const std::vector<std::unique_ptr<T>>& data, const string type)
{
    try
    {
        std::ofstream outFile;
        if (std::string(type) == "student")
        {
            outFile.open(stuFile, std::ios_base::app); // Append mode
            if (!outFile)
            {
                std::cout << "** Failed to open the student file." << std::endl;
                return;
            }

            for (const auto& student : data)
            {
                outFile << student->getFormattedData() << std::endl;
            }
        }
        else if (std::string(type) == "admin")
        {
            outFile.open(adminFile, std::ios_base::app); // Append mode
            if (!outFile)
            {
                std::cout << "** Failed to open the admin file." << std::endl;
                return;
            }

            for (const auto& admin : data)
            {
                outFile << admin->getFormattedData() << std::endl;
            }
        }
        else if (std::string(type) == "room")
        {
            outFile.open(roomFile, std::ios_base::app); // Append mode
            if (!outFile)
            {
                std::cout << "** Failed to open the admin file." << std::endl;
                return;
            }

            for (const auto& room : data)
            {
                outFile << room->getFormattedData() << std::endl;
            }
        }
       else if (std::string(type) == "survey")
        {
            outFile.open(roomFile, std::ios_base::app); // Append mode
            if (!outFile)
            {
                std::cout << "** Failed to open the admin file." << std::endl;
                return;
            }

            for (const auto& room : data)
            {
                outFile << room->getFormattedData() << std::endl;
            }
        }        
        outFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


std::vector<std::unique_ptr<Student>> DataBase::student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw,
 const std::string& class_, const std::string& room, const bool gender, const std::string& mateID, const std::string& surveyId)
{
    std::string val = roadLatestData("student");
    int latePk = stoi(val.substr(0, val.size() - 1));
    if(latePk != 0)
    {
        count_student = latePk;
    }
    count_student++;
    
    std::vector<std::unique_ptr<Student>> studentData;
    std::string s = "s";
    std::string studentId = std::to_string(count_student) + s;
    studentData.push_back(std::make_unique<Student>(studentId, code, name, id, pw, class_, room, gender, mateID, surveyId));
    return studentData;
}


std::vector<std::unique_ptr<Admin>> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::string val = roadLatestData("admin");
    int latePk = stoi(val.substr(0, val.size() - 1));
    if(latePk != 0)
    {
        count_admin = latePk;
    }
    count_admin++;
    std::vector<std::unique_ptr<Admin>> adminData;
        std::string a = "a";
    std::string adminId = std::to_string(count_admin) + a;
    adminData.push_back(std::make_unique<Admin>(adminId, name, id, pw));
    return adminData;
}

std::vector<std::unique_ptr<Room>> DataBase::room_JSON(const std::string& roomNumber, const bool is_empty, const bool status)
{
    std::string val = roadLatestData("room");
    int latePk = stoi(val.substr(0, val.size() - 1));
    if(latePk != 0)
    {
        count_room = latePk;
    }
    count_room++;
    std::vector<std::unique_ptr<Room>> roomData;
    std::string r = "r";
    std::string roomId = std::to_string(count_room) + r;
    roomData.push_back(std::make_unique<Room>(roomId, roomNumber, is_empty, status));
    return roomData;
}

template void DataBase::insert<Student>(const std::vector<std::unique_ptr<Student>>& data, const std::string type);
template void DataBase::insert<Admin>(const std::vector<std::unique_ptr<Admin>>& data, const std::string type);
template void DataBase::insert<Room>(const std::vector<std::unique_ptr<Room>>& data, const std::string type);

std::string DataBase::roadLatestData(const std::string type)
{
    std::ifstream outFile;
    std::string load = findDB(type);
    outFile.open(load, std::ios_base::app); // Append mode
    if (!outFile)
    {
        std::cout << "** Failed to open the student file." << std::endl;
        return "";
    }

    std::string line;
    std::string last_line;
    std::vector<std::string> words;
    std::string word;
    // Read each line from the file
    while (std::getline(outFile, line)) {
        // Save the line
        last_line = line;
    }

    std::stringstream result(last_line);
    while (getline(result, word, ','))
    words.push_back(word);
    // Close the file
    outFile.close();
    return words[0];
}

std::string DataBase::findOne(const std::string type, std::string val, int index)
{
    try
    {
        std::string directory = findDB(type);
        std::ifstream fin(directory);
        std::string line;
        std::vector<std::string> words;
        std::string word;


        while (std::getline(fin, line))
        {
            if(line.find(val) != std::string::npos) 
            {
                std::stringstream result(line);
                while (getline(result, word, ','))
                words.push_back(word);
                break;
            }
            
        }

        if(words.empty())
        {
            throw NotFoundedException();
        }

        fin.close();

        if(words[index].size())
        {
            return words[index];
        }
        else
        {
            return "404 Not Founded : out of range";
        }
        

        return "404 Not Founded : out of range";
    }
    catch(const NotFoundedException& e)
    {
        //std::cout << "404 Not Founded" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return "";
}

std::string DataBase::findAll(const std::string type, std::string val)
{
    try
    {
        std::string directory = findDB(type);
        std::ifstream fin(directory);
        std::vector<std::string> lines;
        std::string line;


        while (std::getline(fin, line))
        {
            if(line.find(val) != std::string::npos)
            {
                lines.push_back(line);
                break;
            }
        }

        if(lines.empty())
        {
            std::cout << "404" << std::endl;
        }

        fin.close();
        
        for (const auto& line : lines)
        {
            std::cout << line << std::endl;
        }
        
        return line;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return "";
}

void DataBase::update(const std::string type, std::string primaryKey, std::string content, int index)
{
    try
    {
        std::string directory = findDB(type);
        std::ifstream fin(directory);
        std::ofstream fout("temp.txt");  // ï¿½Ï½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
        //std::cout << directory << std::endl;

        try
        {
            if (fin.is_open() && fout.is_open())
            {
                std::string line;
                bool updated = false;

                while (std::getline(fin, line))
                {
                    std::istringstream result(line);
                    std::string word;
                    std::vector<std::string> words;

                    while (std::getline(result, word, ','))
                    {
                        words.push_back(word);
                    }
            
                    if (words[0] == primaryKey) // ï¿½Ì°É·ï¿½ ï¿½ï¿½ï¿½Ìºï¿½ & row ï¿½ï¿½ï¿½ï¿½
                    {
                        // string ï¿½ï¿½ï¿½ï¿½
                        int i;
                        std::string newData = "";
                        for(i = 0; i < index; i++)
                        {
                            newData = newData + words[i] + ',';
                        }
                        newData = newData + content + ',';
                        for(i++; i < words.size(); i++)
                        {
                            newData = newData + words[i] + ',';
                        }
                        newData.pop_back();
                        fout << newData << "\n";  // ï¿½ï¿½ï¿½î¾²ï¿½ï¿½
                        updated = true;
                        //std::cout << "out" <<std::endl;
                    }
                    else
                    {
                        fout << line << "\n";  // ï¿½ï¿½ï¿½Ð½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ö±ï¿½
                    }

                    words.clear();
                }

                fin.close();
                fout.close();

                if (updated)
                {
                    std::remove(directory.c_str());
                    std::rename("temp.txt", directory.c_str());
                }
                else
                {
                    std::remove("temp.txt");
                    throw NotFoundedException();
                }
            }
        }
        catch(const NotFoundedException& e)
        {
            //std::cout << "404 Not Founded" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string DataBase::findDB(const std::string type)
{
    try
    {
        std::string directory = "";
        if(std::string(type) == "student")
        {
            directory.clear();
            directory = "DB/student.txt";
        }
        else if (std::string(type) == "admin")
        {
            directory.clear();
            directory = "DB/admin.txt";
        }
        else if (std::string(type) == "room")
        {
            directory.clear();
            directory = "DB/room.txt";

        }
        else if (std::string(type) == "survey")
        {
            directory.clear();
            directory = "DB/survey.txt";

        }
        else
        {
            throw NotFoundedDataBaseException();
        }

        return directory;
    }
    catch(const NotFoundedDataBaseException& e)
    {
        std::cout << "NotFoundedDataBaseException '"<< type << "'" << std::endl;
    }

    return "";
}

bool DataBase::findUser(const string userType, const string userId, const string userPw)
{
    if (findOne(userType, userId, 3) == userId && findOne(userType, userPw, 4) == userPw && userType=="student")
    {
        return true;
    }
    else if (findOne(userType, userId, 2) == userId && findOne(userType, userPw, 3) == userPw&& userType=="admin")
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> DataBase::getLineFromId(const string userType, const string userId)
{
    std::vector<std::string> lines;
    try
    {
        std::string directory = findDB(userType);
        std::ifstream fin(directory);        
        std::string line;

        while (std::getline(fin, line))
        {
            std::istringstream iss(line);
            std::string str_buf;
            char separator = ',';
            
            lines.clear();
            while (getline(iss, str_buf, separator))
            {
                lines.push_back(str_buf);
                //std::cout << str_buf << std::endl;
            }
            int ca = 0;
            if(lines.at(3) == userId && userType == "student")
            {
                //std::cout << ">> ingetlineformid \n" << std::endl;
                for (const auto& str : lines) {
                    std::cout << ">> "<< ca << " : "<< str << std::endl;
                    ca++;
                }
                return lines;
            }
            if(lines.at(1) == userId && userType == "admin")
            {
                return lines;
            }
        }
    }
    catch(const NotFoundedDataBaseException& e)
    {
        cout << "error"<<endl;
    }
    return lines;
}



unique_ptr<User> DataBase::getUser(const string userType, const string userId, const string userPw)
{
    
	try{
		if(findUser(userType, userId, userPw))
		{
            vector<string> userInfo;
            userInfo = getLineFromId(userType,userId);
			if(userType == "admin")
			{
				return make_unique<Admin>(userInfo.at(0),userInfo.at(1), userInfo.at(2), userInfo.at(3));
			}
			else if (userType == "student")
			{
                bool setGern = true;
                if(userInfo.at(6) != "Male") { setGern = false;}
                return make_unique<Student>(userInfo.at(0),stoi(userInfo.at(1)),userInfo.at(2), userInfo.at(3), userInfo.at(4), userInfo.at(5),userInfo.at(8), setGern, userInfo.at(9),userInfo.at(10));
			}
		}
		else
		{
			throw NotFoundedDataBaseException();
		}
	}
	catch(const NotFoundedDataBaseException& e)
	{
		//cout << "404 Not Founded" <<endl;
	}

    return make_unique<Student>("",0,"","","","","",'a',"", "");
}


std::string DataBase::insertSurvey(vector<std::string> data)

{
    std::ofstream outFile;
    std::string load = "DB/survey.txt";
    outFile.open(load, std::ios_base::app); // Append mode
    if (!outFile)
    {
        std::cout << "** Failed to open the student file." << std::endl;
        return"";
    }
    std::string val = roadLatestData("survey");
    int latePk = stoi(val.substr(0, val.size() - 1));
    if(latePk != 0)
    {
        count_survey = latePk;
    }
    count_survey++;
    std::string index = "su,";
    std::string add = to_string(count_survey) + index;
    std::string returnAdd;
    returnAdd = add;
    std::string result = std::accumulate(data.begin(), data.end(), std::string());
    
    // Add a newline character
    add += result;
    outFile << add;
    outFile << endl;
    // Close the file
    outFile.close();
    returnAdd.pop_back();
    return returnAdd;
}
vector<vector<string>> DataBase::readSurvey()
{
    vector<vector<string>>readsurvey;
    std::ifstream file("DB/survey.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> answers;
            std::string answer;
            while (std::getline(iss, answer, ',')) {
                answers.push_back(answer);
            }
            readsurvey.push_back(answers);
        }
        file.close();
    }
    else {
        std::cout << "** Failed to open the file." << std::endl;
    }


    return readsurvey;
}

vector<vector<string>>DataBase::readtxt(const string type)
{
    vector<vector<string>>readtxt;
    string txt = "DB/"+type + ".txt";
    std::ifstream file(txt);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> answers;
            std::string answer;
            while (std::getline(iss, answer, ',')) {
                answers.push_back(answer);
            }
            readtxt.push_back(answers);
        }
        file.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }


    return readtxt;

}

void DataBase::addingStudent(int code, string name, string id, string pw, string class_, string room, bool gender, string mateID)
{
    vector<unique_ptr<Student>> stu = student_JSON(code, name, id, pw, class_, room, gender, mateID);
    insert(stu, "student");
    return;
}
    
std::string getPkNum(std::string line)
{
    std::vector<std::string> words;
    std::string word;

    std::stringstream result(line);
    while (getline(result, word, ','))
    words.push_back(word);
    // Close the file
    return words[0];
}

void DataBase::Delete(const std::string type, std::string lineToDelete) {
    std::string line;

    if(findOne(type, lineToDelete, 0) != lineToDelete) { return; }

    std::string filename = findDB(type);
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "** Failed to open the file." << std::endl;
        return;
    }

    std::string tempFilename = filename + ".tmp";
    std::ofstream tempFile(tempFilename);
    if (!tempFile) {
        std::cout << "** Failed to create the temporary file." << std::endl;
        inputFile.close();
        return;
    }

    
    while (std::getline(inputFile, line)) {
        if (getPkNum(line) != lineToDelete) {
            tempFile << line << std::endl;
        }
    }
    

    inputFile.close();
    tempFile.close();


    if (std::remove(filename.c_str()) != 0) {
        std::cout << "** Failed to delete the original file." << std::endl;
        return;
    }

    if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
        std::cout << "** Failed to rename the temporary file." << std::endl;
        return;
    }

    //std::cout << ">> Line " << lineToDelete << " deleted successfully." << std::endl;
}
