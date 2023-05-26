// database.cpp
#include "DataBase.h"
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"
#include <typeinfo>

int count_room = 0;
int count_student = 0;
int count_admin = 0;

class NotFoundedDataBaseException {

};

class NotFoundedException {

};

template <typename T>
void DataBase::insert(const std::vector<std::unique_ptr<T>>& data, const char* type)
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

std::vector<std::unique_ptr<Student>> DataBase::student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw, const std::string& class_, int room)
{
    std::vector<std::unique_ptr<Student>> studentData;
    count_student++;
    std::string s = "s";
    std::string studentId = std::to_string(count_student) + s;
    studentData.push_back(std::make_unique<Student>(studentId, code, name, id, pw, class_, room));


    return studentData;
}

std::vector<std::unique_ptr<Admin>> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::vector<std::unique_ptr<Admin>> adminData;
    count_admin++;
    std::string a = "a";
    std::string adminId = std::to_string(count_admin) + a;
    adminData.push_back(std::make_unique<Admin>(adminId, name, id, pw));

    return adminData;
}

std::vector<std::unique_ptr<Room>> DataBase::room_JSON(const std::string& roomNumber, const bool is_empty)
{
    std::vector<std::unique_ptr<Room>> roomData;
    count_room++;
    std::string r = "r";
    std::string roomId = std::to_string(count_room) + r;
    roomData.push_back(std::make_unique<Room>(roomId, roomNumber, is_empty));
    return roomData;
}

template void DataBase::insert<Student>(const std::vector<std::unique_ptr<Student>>& data, const char* type);
template void DataBase::insert<Admin>(const std::vector<std::unique_ptr<Admin>>& data, const char* type);
template void DataBase::insert<Room>(const std::vector<std::unique_ptr<Room>>& data, const char* type);

std::string DataBase::findOne(const char* type, std::string val, int index)
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

std::string DataBase::findAll(const char* type, std::string val)
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

void DataBase::update(const char* type, std::string primaryKey, std::string content, int index)
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
/*
깃풀 테스트용 주석 코듬ㅁ나ㅐㅁ넞야
*/
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

std::string DataBase::findDB(const char* type)
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