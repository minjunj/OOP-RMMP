#include "DataBase.h"
#include "../student/student.h"
#include "../admin/admin.h"
#include "../room/room.h"
#include <memory.h>
template <typename T>
void DataBase::insert(const std::vector<std::shared_ptr<T>>& data, const char* type)
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

    template void DataBase::insert<Student>(const std::vector<std::shared_ptr<Student>>& data, const char* type);
    template void DataBase::insert<Admin>(const std::vector<std::shared_ptr<Admin>>& data, const char* type);
    template void DataBase::insert<Room>(const std::vector<std::shared_ptr<Room>>& data, const char* type);

std::vector<std::shared_ptr<Student>> DataBase::student_JSON(int code, const std::string& name, const std::string& id, const std::string& pw, const std::string& class_, int room)
{
    std::vector<std::shared_ptr<Student>> studentData = {
        std::make_shared<Student>(code, name, id, pw, class_, room)
    };

    return studentData;
}

std::vector<std::shared_ptr<Admin>> DataBase::admin_JSON(const std::string& name, const std::string& id, const std::string& pw)
{
    std::vector<std::shared_ptr<Admin>> adminData = {
        std::make_shared<Admin>(name, id, pw)
    };

    return adminData;
}

std::vector<std::shared_ptr<Room>> DataBase::room_JSON(const std::string& roomID, const std::string& roomNumber, const bool is_empty)
{
    std::vector<std::shared_ptr<Room>> roomData = {
        std::make_shared<Room>(roomID, roomNumber, is_empty)
    };

    return roomData;
}
