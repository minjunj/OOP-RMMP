// room.h

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataBase; // Forward declaration of DataBase class

/*
    [1] roomID : auto increased
    [2] roomNumber,
    [3] is_empty
*/
class Room {
private:
    std::string roomId; //auto increased
    std::string roomNumber;
    bool is_empty;

    friend class DataBase;

public:
    Room(const std::string& roomId, const std::string& roomNumber, const bool is_empty);

    std::string getFormattedData() const; // DB용
};

#endif
