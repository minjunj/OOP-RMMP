#include "DataBase.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void DataBase::inputData(int num)
{
    stuInfoTable.clear();
    ifstream readFile;
    if (num == 1)
    {
        readFile.open(stuFile);
        stuInfoTable.clear();
    }
    else if (num == 2)
    {
        readFile.open(adminFile);
        adminInfoTable.clear();
    }
    else if (num == 3)
    {
        readFile.open(dormFile);
        dormInfoTable.clear();
    }
    else return;


    if (readFile.is_open())
    {
        string line;
        while (getline(readFile, line))
        {
            istringstream ss(line);
            vector <string> temp;
            string word;
            while (getline(ss, word, ' '))
            {
                temp.push_back(word);
            }
            if (num == 1) stuInfoTable.push_back(temp);
            if (num == 2) adminInfoTable.push_back(temp);
            if (num == 3) dormInfoTable.push_back(temp);
        }
        readFile.close();
    }

    return;
}
void DataBase::printData(int num)
{
    if (num == 1)
    {
        for (const auto& row : stuInfoTable)
        {
            for (const auto& element : row)
            {
                cout << element << " ";
            }
            cout << endl;
        }
    }
    else if (num == 2)
    {
        for (const auto& row : adminInfoTable)
        {
            for (const auto& element : row)
            {
                cout << element << " ";
            }
            cout << endl;
        }
    }
    else if (num == 3)
    {
        for (const auto& row : dormInfoTable)
        {
            for (const auto& element : row)
            {
                cout << element << " ";
            }
            cout << endl;
        }
    }
    else return;
}

void DataBase::outputData(int num, string sen)
{
    ofstream writeFile;
    if (num == 1)
    {
        writeFile.open(stuFile, ios_base::out | ios_base::app);
    }
    else if (num == 2)
    {
        writeFile.open(adminFile, ios_base::out | ios_base::app);
    }
    else if (num == 3)
    {
        writeFile.open(dormFile, ios_base::out | ios_base::app);
    }
    else return;

    for (int i = 0; i < 10; i++)
    {
        writeFile << i;
    }


    if (writeFile.is_open())
    {
        string line;

        istringstream ss(line);
        vector <string> temp;
        string word;
        while (getline(ss, word, ' '))
        {
            writeFile << word << " ";
            temp.push_back(word);
        }
        writeFile << endl;

        if (num == 1) stuInfoTable.push_back(temp);
        if (num == 2) adminInfoTable.push_back(temp);
        if (num == 3) dormInfoTable.push_back(temp);
    }

    writeFile.close();
}

void DataBase::deleteData(int num, string ID)
{
    ifstream readFile;
    ofstream tempFile;

    string fileName;
    string line;

    if (num == 1) fileName = stuFile;
    else if (num == 2) fileName = adminFile;
    else if (num == 3) fileName = dormFile;
    else return;
    readFile.open(fileName);
    tempFile.open("temp.txt");

    while (getline(readFile, line))
    {
        if (line.find(ID) != string::npos)
        {
            tempFile << line << endl;
        }
    }
    tempFile.close();
    readFile.close();

    const char* p = fileName.c_str();
    remove(p);
    rename("temp.txt", p);

    return;
}

void DataBase::createFile(string fileName)
{
    fstream newFile(fileName);
    cout << fileName << "file is created!" << endl;
    return;
}

