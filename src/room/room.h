// room.h

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataBase; // Forward declaration of DataBase class

/*
    string : roomID,
    string : roomNumber,
    bool : is_empty
*/
class Room {
private:
    std::string roomID; //auto increase
    std::string roomNumber;
    bool is_empty;

    friend class DataBase;

public:
    Room(const std::string& roomID, const std::string& roomNumber, const bool is_empty);

    std::string getFormattedData() const; // DB용
};

#endif
