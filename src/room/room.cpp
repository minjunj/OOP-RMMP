// room.cpp

#include "room.h"
#include <vector>
#include <string>
Room::Room(const std::string& roomId, const std::string& roomNumber, const bool is_empty)
    : roomId(roomId), roomNumber(roomNumber), is_empty(is_empty)
{
}

std::string Room::getFormattedData() const {
    std::string emptyString = is_empty ? "true" : "false";
    return roomId + "," + roomNumber + "," + emptyString;
}
