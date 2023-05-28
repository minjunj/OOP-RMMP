# OOP-RMMP

# complie method
#### 디렉토리 이동 move directory
 cd src
 g++ main.cpp ./admin/admin.cpp ./admin/admin.h ./database/DataBase.cpp ./database/DataBase.h ./room/room.cpp ./room/room.h ./student/student.cpp ./student/student.h ./user/User.cpp ./user/User.h -o test -std=c++14
#### std::make_unique realted uniuqe_ptr can surpport in c++14 So, please Compile to C++14

  폴더로 정리해서 컴파일 시 경로를 지정해줘야함.

# commit
 1. local update using "git pull" commed
 2. make new branch <operaotr : report>

 
 # other
 
 ### DB에서 유니크 포인터를 쓴 이유
이 코드에서는 DataBase 클래스의 멤버 함수인 insert에서 std::vector<std::unique_ptr<T>>를 사용하여 데이터를 삽입합니다. 이 함수는 동적으로 할당된 T 타입의 객체에 대한 소유권을 std::unique_ptr로 관리합니다.

또한, DataBase 클래스의 멤버 함수인 student_JSON, admin_JSON, room_JSON에서도 std::vector<std::unique_ptr<T>>를 사용하여 각각 Student, Admin, Room 객체를 동적으로 할당하고 관리합니다.

따라서 주어진 코드에서 std::unique_ptr을 사용하여 포인터를 관리하는 것은 적합한 선택입니다.

# DB API

main에 DataBase db;가 있다는 가정하에 진행
## Set Data

  JsonStu studentData = db.student_JSON(20225180, "new민준", "m412", "pw12", "22", 12); // 데이터 셋팅

  JsonAdmin adminData = db.admin_JSON("name", "mw412", "pww12");

  JsonRoom roomData = db.room_JSON("T217", false); // id가 자동으로 오름.

### insert DB
  (보낼 JSON, 목적지 테이블 명)

  db.insert(studentData, "student"); //db에 삽입

  db.insert(adminData, "admin");

  db.insert(roomData, "room");

### findOne DB
  (조회할 테이블 명, 조회할 데이터, 보고 싶은 파트)

  db.findOne("student", "id123id", 2);

  db.findOne("student", "p123p", 3);


  ex. 유저 로그인 확인

  if (loginId == db.findOne("student", loginId, 2) &&  loginPw == db.findOne("student", loginId, 3))
  {
    return "login success";
  }

 리턴값은 그냥 string 하나만 줌.
### findAll DB
  (조회 위치, 찾을 정보)
  db.findAll("admin", "mw4121");
 리턴값은 2s,20225180,조민준1,content,pw121,221,user,121 이런식으로 string으로 줌
### update DB
 (조회 위치, 바꿀 정보, 바꿀 정보의 인덱스)
  db.findOne("student", "m4121", 1)

### db.checkRoom(); 
  DataBase에서 새로 들어줘야할 함수, 현재 기숙사의 전체적인 현황(비어있는지, 방에 몇명 있는지 등) 한 눈에 볼 수 있는 함수가 필요 필요함
  main.cpp 173줄 참고
