// room.cpp

#include "room.h"
#include <vector>
#include <string>
Room::Room(const std::string& roomID, const std::string& roomNumber, const bool is_empty)
    : roomID(roomID), roomNumber(roomNumber), is_empty(is_empty)
{
}

std::string Room::getFormattedData() const {
    std::string emptyString = is_empty ? "true" : "false";
    return roomID + "," + roomNumber + "," + emptyString;
}
