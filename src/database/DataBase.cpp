// database.cpp
#include "DataBase.h"
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"
#include <typeinfo>
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
    studentData.push_back(std::make_unique<Student>(code, name, id, pw, class_, room));


    return studentData;
}

std::vector<std::unique_ptr<Admin>> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::vector<std::unique_ptr<Admin>> adminData;
    adminData.push_back(std::make_unique<Admin>(name, id, pw));

    return adminData;
}

std::vector<std::unique_ptr<Room>> DataBase::room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty)
{
    std::vector<std::unique_ptr<Room>> roomData;
    roomData.push_back(std::make_unique<Room>(roomID, roomNumber, is_empty));
    return roomData;
}

template void DataBase::insert<Student>(const std::vector<std::unique_ptr<Student>>& data, const char* type);
template void DataBase::insert<Admin>(const std::vector<std::unique_ptr<Admin>>& data, const char* type);
template void DataBase::insert<Room>(const std::vector<std::unique_ptr<Room>>& data, const char* type);

std::string DataBase::findOne(const char* type, std::string val, int index)
{
    std::string directory = "";
    if(std::string(type) == "student")
    {
        directory.clear();
        directory = "student.txt";
    }
    else if (std::string(type) == "admin")
    {
        directory.clear();
        directory = "admin.txt";
    }
    else if (std::string(type) == "room")
    {
        directory.clear();
        directory = "room.txt";

    }
    else
    {
        throw std::out_of_range("해당하는 DB테이블을 찾을 수 없음");
    }
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
        std::cout << "404 Not Founded" << std::endl;
    }

    fin.close();
    try
    {
        if(words[index].size())
        {
            return words[index];
        }
    }
    catch(...)
    {
        throw std::out_of_range("404 Not Founded : out of range");
    }
    

    return "404 Not Founded : out of range";
}
// 뭐 만약에 유저 로긴해서 id pw 봄 id 있는지 볼 떄 저걸로 db.FindOne("student", "exid2", 2) 로 아이디 일치하고, db.FindOne("student", "expass", 3) 받아서 확인.
