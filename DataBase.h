#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class DataBase
{
private:
	string stuFile = "studentFile.txt";
	string adminFile = "adminFile.txt";
    string dormFile = "dormFile.txt";
    vector <vector <string>> stuInfoTable;
    vector <vector <string>> adminInfoTable;
    vector <vector <string>> dormInfoTable;

public:
    // Entering data from file to vector
    void inputData(int num);
    void printData(int num);
    void deleteData(int num, string ID);
    void outputData(int num, string sen);

    void createFile(string fileName);

    void print();
};

