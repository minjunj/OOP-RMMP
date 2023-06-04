// database.cpp
#include "DataBase.h"
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"
#include <typeinfo>
#include <memory>
#include <numeric>
int count_room = 0;
int count_student = 0;
int count_survey = 0;

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
                std::cout << "Failed to open the student file." << std::endl;
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
                std::cout << "Failed to open the admin file." << std::endl;
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
                std::cout << "Failed to open the admin file." << std::endl;
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


std::vector<std::unique_ptr<Student>> DataBase::student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw, const std::string& class_, const std::string& room, const bool gender, const std::string& mateID)

{
    std::vector<std::unique_ptr<Student>> studentData;
    count_student++;
    std::string s = "s";
    std::string studentId = std::to_string(count_student) + s;

    studentData.push_back(std::make_unique<Student>(studentId, code, name, id, pw, class_, room, gender, mateID));
    return studentData;
}

std::vector<std::unique_ptr<Admin>> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::vector<std::unique_ptr<Admin>> adminData;
    adminData.push_back(std::make_unique<Admin>(name, id, pw));
    return adminData;
}

std::vector<std::unique_ptr<Room>> DataBase::room_JSON(const std::string& roomNumber, const bool is_empty, const bool status)
{
    std::vector<std::unique_ptr<Room>> roomData;
    count_room++;
    std::string r = "r";
    std::string roomId = std::to_string(count_room) + r;
    roomData.push_back(std::make_unique<Room>(roomId, roomNumber, is_empty, status));
    return roomData;
}

template void DataBase::insert<Student>(const std::vector<std::unique_ptr<Student>>& data, const std::string type);
template void DataBase::insert<Admin>(const std::vector<std::unique_ptr<Admin>>& data, const std::string type);
template void DataBase::insert<Room>(const std::vector<std::unique_ptr<Room>>& data, const std::string type);

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
            if(line.find(val) != std::string::npos) // 원하는 row 찾기
            {
                std::stringstream result(line);
                while (getline(result, word, ','))
                words.push_back(word);
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
        std::cout << "404 Not Founded" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return "";
}
// 뭐 만약에 유저 로긴해서 id pw 봄 id 있는지 볼 떄 저걸로 db.FindOne("student", "exid2", 2) 로 아이디 일치하고, db.FindOne("student", "expass", 3) 받아서 확인.

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
        std::ofstream fout("temp.txt");  // 일시저장용
        std::cout << directory << std::endl;

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
            
                    if (words[0] == primaryKey) // 이걸로 테이블 & row 구분
                    {
                        // string 제작
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
                        fout << newData << "\n";  // 덮어쓰기
                        updated = true;
                        std::cout << "out" <<std::endl;
                    }
                    else
                    {
                        fout << line << "\n";  // 실패시 원래 라인 넣기
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
            std::cout << "404 Not Founded" << std::endl;
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
	if (findOne(userType, userId, 3) == userId && findOne(userType, userPw, 4) == userPw)
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
                std::cout << str_buf << std::endl;
            }
            if(lines.at(3) == userId && userType == "student")
            {
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
				return make_unique<Admin>(userInfo.at(0),userInfo.at(1), userInfo.at(2));
			}
			else if (userType == "student")
			{
                return make_unique<Student>(userInfo.at(0),stoi(userInfo.at(1)),userInfo.at(2), userInfo.at(3), userInfo.at(4), userInfo.at(5), userInfo.at(6),userInfo.at(7)[0],userInfo.at(8));
			}
		}
		else
		{
			throw NotFoundedDataBaseException();
		}
	}
	catch(const NotFoundedDataBaseException& e)
	{
		cout << "404 Not Founded" <<endl;
	}
    return make_unique<Student>("",0,"","","","","",'a',"");
} // 새로 필요한 함수


void DataBase::insertSurvey(vector<std::string> data)
{
    std::ofstream outFile;
    std::string load = "DB/survey.txt";
    outFile.open(load, std::ios_base::app); // Append mode
    if (!outFile)
    {
        std::cout << "Failed to open the student file." << std::endl;
        return;
    }
    count_survey++;
    std::string index = "su,";
    std::string add = to_string(count_survey) + index;
    std::string result = std::accumulate(data.begin(), data.end(), std::string());
    
    // Remove the trailing comma
    if (!result.empty())
    {
        result.pop_back();
    }

    
    // Add a newline character
    result += '\n';
    add += result;
    outFile << add;
    // Close the file
    outFile.close();
}


void DataBase::addingStudent(int code, string name, string id, string pw, string class_, string room, bool gender, string mateID)
{
    vector<unique_ptr<Student>> stu = student_JSON(code, name, id, pw, class_, room, gender, mateID);
    insert(stu, "student");
    return;
}
    

