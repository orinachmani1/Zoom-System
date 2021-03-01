#ifndef EX5_STUDENT_H
#define EX5_STUDENT_H

#include <string>
#include <vector>
#include <iterator>
#include "message.h"
#include "Room.h"

using namespace std;
class Room;

class Student{
private:
    string firstName;
    string lastName;
    int id;
    double average;
    int roomID;
    Room* myRoom;
    vector <message*> messages;

public:
    Student(string fn, string ls, int id, double average);
    virtual ~Student();
    void receiveMassage(message* m);
    void printStudent();
    virtual void split_yourself(Room* r,Room* L,Room* R)=0;
    virtual void work_message()=0;
    virtual void send_message_to_class(string content)=0;
    virtual void cry()=0;

    string get_first_name(){return this->firstName;}
    string get_last_name(){return this->lastName;}
    int get_average(){return this->average;}
    int get_id(){return this->id;}
    int get_roomID(){return this->roomID;}
    void set_roomID(int room_id){this->roomID = room_id;}
    Room* get_room(){return this->myRoom;}
    vector <message*> getMassages(){return this->messages;}
    void set_room(Room* r){this->myRoom = r;}
    void print_all_messages();
};

#endif //EX5_STUDENT_H
