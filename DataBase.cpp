// DataBase.cpp

#include "DataBase.h"
#include "student.h"
#include "admin.h"
#include "room.h"

/*insert( _JSON으로 저장한 data, 저장위치 : admin, student, room)*/
template <typename T>
void DataBase::insert(const std::vector<T>& data, const char* type)
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
                outFile << student.getFormattedData() << std::endl;
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
                outFile << admin.getFormattedData() << std::endl;
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
                outFile << room.getFormattedData() << std::endl;
            }
        }
        outFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

template void DataBase::insert<Student>(const std::vector<Student>& data, const char* type);
template void DataBase::insert<Admin>(const std::vector<Admin>& data, const char* type);
template void DataBase::insert<Room>(const std::vector<Room>& data, const char* type);

std::vector<Student> DataBase::student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw, const std::string& class_, int room)
{
    std::vector<Student> studentData = {
        Student(code, name, id, pw, class_, room)
    };

    return studentData;
}

std::vector<Admin> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::vector<Admin> adminData = {
        Admin(name, id, pw)
    };

    return adminData;
}

std::vector<Room> DataBase::room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty)
{
    std::vector<Room> roomData = {
        Room(roomID, roomNumber, is_empty)
    };

    return roomData;
}
