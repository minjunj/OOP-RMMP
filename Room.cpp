#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Room.h"
//#include"Database.h"
using namespace std;

bool Room::isEmpty() {
/*	if () {
		return 0;
	}*/
	return 1;
}

string Room::getRoomID() {
	return this->roomID;
}
int Room::getRoomFloor() {
	return this->roomFloor;
}

int* Room::getResidentStuId() {
	return this->residentStuId;
}
