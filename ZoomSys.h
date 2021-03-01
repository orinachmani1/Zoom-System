#ifndef EX5_ZOOMSYS_H
#define EX5_ZOOMSYS_H

#include "Student.h"
#include "Room.h"
class ZoomSys {

private:
    vector <Room*> root_rooms;
    vector <Student*> all_students;
    Room* locate_room(Room* curr_room, int id);
public:
    ZoomSys(const char* c);
    ~ZoomSys();
    void addStudent();
    void assignStudent();
    void removeStudent();
    void removeRoom();
    void addRoom();
    void splitRoom();
    void work();
    void sendMessage();
    void printRooms();
    void printStudents();
    void printStudentDetails();
    Room* get_room_by_id(int id);
    Student* get_student_by_id(int id);
};

#endif //EX5_ZOOMSYS_H
