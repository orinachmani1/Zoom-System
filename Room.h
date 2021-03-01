#ifndef EX5_ROOM_H
#define EX5_ROOM_H
#include <string>
#include <vector>
#include "Student.h"

using namespace std;

class Student;
class Room{
protected:
    static int roomsCounter;
    int id;
    int num_of_students;
    Room* Left;
    Room* Right;
    Room* father;
    vector <Student*> all_students;
    Student* get_student_by_id(int id);
    void split_room_by_character();
    void split_room_by_quantity();


public:
    Room();
    virtual ~Room();
    void add_student(Student* s);
    void remove_student(Student* s);
    void remove_student(int id);
    void removeRoom();
    void split_room(int split_type);

    void printRoom();
    void print_students();

    static int getID(){return roomsCounter;}
    vector <Student*>* get_students(){return &(this->all_students);}
    int get_num_of_students(){return this->num_of_students;}
    void raise_num_of_students(){this->num_of_students++;}
    void sub_num_of_students(){this->num_of_students--;}
    int get_id(){return this->id;}
    Room* getLeft(){ return this->Left;}
    Room* getRight(){ return this->Right;}
    Room* getFather(){ return this->father;}
    void setLeft(Room* r){this->Left = r;}
    void setRight(Room* r){this->Right = r;}
    void getFather(Room* r){this->father = r;}

};

#endif //EX5_ROOM_H
