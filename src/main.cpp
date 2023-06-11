// main.cpp
#include <iostream>
#include <string>
#include <memory>
#include "./user/User.h"
#include "./database/DataBase.h"
#include "./student/student.h"
#include "./admin/admin.h"
#include "./room/room.h"
#include "./templates.h"
#include "./menu.h"
using namespace std;
using JsonStu = std::vector<std::unique_ptr<Student>>;
using JsonAdmin = std::vector<std::unique_ptr<Admin>>;
using JsonRoom = std::vector<std::unique_ptr<Room>>;


void versionCheck()
{
    std::cout << "========================================"<<endl<<endl;
    std::cout << " #####    ##     ##  ##     ##   #####  "<<endl;
    std::cout << " ##   ##  #### ####  #### ####  ##      "<<endl;
    std::cout << " #####    ## ### ##  ## ### ##    ###  "<<endl;
    std::cout << " ##  ##   ##     ##  ##     ##      ##  "<<endl;
    std::cout << " ##   ##  ##     ##  ##     ##  #####   "<<endl<<endl;
    std::cout << "========================================"<<endl;
    std::cout << " V1.0 Roommate Matching System for GIST"<<endl;
    std::cout << " Built By Hyunwoo Lee, Minjun Jo, Minjae Jo"<<endl<<endl;
}

int main()
{
    DataBase db;

    versionCheck();
    start_menu(db);    

    return 0;
}