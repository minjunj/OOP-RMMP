#ifndef ROOM_H
#define ROOM_H
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
//#include"Database.h"

using namespace std;

class Room {
	string roomID;
	int roomFloor;
	int residentStuId[10];
public:
	bool isEmpty();
	string getRoomID();
	int getRoomFloor();
	int* getResidentStuId();

};


#endif
