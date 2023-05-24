# OOP-RMMP

# complie method
 // move directory
 cd src
 g++ main.cpp ./admin/admin.cpp ./admin/admin.h ./database/DataBase.cpp ./database/DataBase.h ./room/room.cpp ./room/room.h ./student/student.cpp ./student/student.h ./user/User.cpp ./user/User.h -o test -std=c++14
 // std::make_unique realted uniuqe_ptr can surpport in c++14

  폴더로 정리해서 컴파일 시 경로를 지정해줘야함.

# commit
 1. local update using "git pull" commed
 2. make new branch <operaotr : report>

 
 # other
 
 ### DB에서 유니크 포인터를 쓴 이유
이 코드에서는 DataBase 클래스의 멤버 함수인 insert에서 std::vector<std::unique_ptr<T>>를 사용하여 데이터를 삽입합니다. 이 함수는 동적으로 할당된 T 타입의 객체에 대한 소유권을 std::unique_ptr로 관리합니다.

또한, DataBase 클래스의 멤버 함수인 student_JSON, admin_JSON, room_JSON에서도 std::vector<std::unique_ptr<T>>를 사용하여 각각 Student, Admin, Room 객체를 동적으로 할당하고 관리합니다.

따라서 주어진 코드에서 std::unique_ptr을 사용하여 포인터를 관리하는 것은 적합한 선택입니다.
