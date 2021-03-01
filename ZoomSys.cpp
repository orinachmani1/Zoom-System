#include "ZoomSys.h"
#include "lazy_student.h"
#include "active_student.h"
#include "responsible_student.h"
#include "Room.h"
#include "active_room.h"
#include "lazy_room.h"
#include "My_Exceptions.h"
#include<sstream>
#include<fstream>
#include<iostream>

ZoomSys::ZoomSys(const char *c) {
    string line;
    fstream myFile;
    myFile.open(c);

    if (myFile.is_open())
    {
        string EOL = "\n";
        string fn;
        string ln;
        int id;
        int avg;
        char type;

        while ( getline (myFile,line) )
        {
            line =line.substr(0,line.find(EOL));
            istringstream token(line);
            token>>fn;
            token>>ln;
            token>>id;
            token>>avg;
            token>>type;

            if (type == 'R')
            {
                responsible_student* rs = new responsible_student(fn,ln,id,avg);
                this->all_students.push_back(rs);
            }

            if (type == 'L')
            {
                lazy_student* ls = new lazy_student(fn,ln,id,avg);
                this->all_students.push_back(ls);
            }

            if (type == 'W')
            {
                active_student* as = new active_student(fn,ln,id,avg);
                this->all_students.push_back(as);
            }
        }
    }

    myFile.close();
}

void ZoomSys::removeRoom()
{
    cout <<"---Remove Room---" <<endl;
    cout <<"Enter room id:" << endl;
    int id;
    cin>> id;


    try
    {
        Room* r = get_room_by_id(id);
        int index = -1;
        for (int i = 0; i < this->root_rooms.size(); ++i)
        {
            if(this->root_rooms[i]->get_id() == id)
            {
                index = i;
                break;
            }
        }
        if (index != -1){
            root_rooms.erase(root_rooms.begin() + index);
        }
        delete r;


    }

    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }


}

Student* ZoomSys::get_student_by_id(int id)
{
    int index = -1;
    for (int i = 0; i < this->all_students.size(); ++i)
    {
        if(this->all_students[i]->get_id() == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        throw invalidID();
    }
    Student* s = this->all_students[index];
    return s;
}

void ZoomSys::printRooms()
{

//    for (int i = 0; i < this->root_rooms.size(); ++i)
//    {
//        this->root_rooms[i]->printRoom();
//    }
    int max_id = Room::getID();
    for (int i = 0; i < max_id; i++){
        try{
            Room* r = get_room_by_id(i);
            r->printRoom();
        }
        catch (exception &e){
            ;
        }
    }
}

void ZoomSys::printStudents()
{
    cout <<"First name, Last Name, ID, Avg, Room ID" <<endl;
    for (int i = 0; i < this->all_students.size(); ++i)
    {
        this->all_students[i]->printStudent();
    }
}

void ZoomSys::printStudentDetails()
{
    cout <<"Enter student id:" <<endl; // to complit
    int id;
    cin>> id;
    try
    {
        Student* s = get_student_by_id(id);
        s->printStudent();
        s->print_all_messages();
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }
}

void ZoomSys::removeStudent()
{
    cout <<"please enter id" <<endl; // to complit
    int id;
    cin>> id;


    try
    {
        Student* s = get_student_by_id(id);
        Room* r = s->get_room();
        if (r != nullptr)
        {
            r->remove_student(id);
        }

        int index = -1;
        for (int i = 0; i < this->all_students.size(); ++i)
        {
            if(this->all_students[i]->get_id() == id)
            {
                index = i;
                break;
            }
        }
        all_students.erase(all_students.begin()+index);
        delete s;
    }

    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }


}

Room* ZoomSys::locate_room(Room* cur_room, int id){
    if (cur_room->get_id() == id){
        return cur_room;
    }
    if (cur_room->getLeft() != nullptr){
        Room* cand = locate_room(cur_room->getLeft(), id);
        if (nullptr != cand){ return cand;}
    }
    if (cur_room->getRight() != nullptr){
        Room* cand = locate_room(cur_room->getRight(), id);
        if (nullptr != cand){ return cand;}
    }
    return nullptr;

}

Room *ZoomSys::get_room_by_id(int id)
{
    for (int i = 0; i < this->root_rooms.size(); ++i)
    {
        Room* cur_room = locate_room(root_rooms[i], id);
        if (cur_room != nullptr) { return cur_room;}

    }
    throw invalidID();
}

void ZoomSys::addRoom()
{
    Room* sr= new Room();
    cout << "New room created" << endl;
    this->root_rooms.push_back(sr);
}

void ZoomSys::splitRoom()
{
    cout <<"---Split Room---" <<endl;
    cout <<"Room id:" <<endl;
    int id;
    cin>> id;


    try {
        Room *r = this->get_room_by_id(id); // can throw - non existing
        if (r->getLeft() != nullptr || r->getRight() != nullptr){
            throw Split_before();
        }
        cout << "1.Character split" << endl;
        cout << "2.Size split" << endl;
        int input;
        cin >> input;


        if (input != 1 && input != 2) {
            throw invalidDetails();
        }


        r->split_room(input); // can throw - split before
        //this->root_rooms.push_back(r->getLeft());
        //this->root_rooms.push_back(r->getRight());

        /*
        r->print_students();
        r->getLeft()->print_students();
        r->getRight()->print_students();
         */
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }

}

void ZoomSys::work() {
    cout << "Enter the room you want to work:" << endl; // to complit
    int id;
    cin >> id;
    try {
        Room *r = this->get_room_by_id(id);

        vector<Student *> students = *(r->get_students());
        for (int i = 0; i < students.size(); ++i) {
            students[i]->work_message();
        }
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }
}

void ZoomSys::sendMessage()
{
    cout <<"Enter the id:" <<endl; // to complit
    int id;
    cin>> id;

    try
    {
        Student* s = get_student_by_id(id);
        cout <<"Enter the message:" <<endl; // to complit
        string mes;
        cin>> mes;
        s->send_message_to_class(mes);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }

}

void ZoomSys::addStudent()
{
    string fn;
    string ln;
    int id;
    int avg;
    char type;

    cout <<"---Create Student---" <<endl;
    cout <<"First name:" <<endl;
    cin>> fn;
    cout <<"Last name:" <<endl;
    cin>> ln;
    cout <<"ID:" <<endl;
    cin>> id;
    cout <<"avg:" <<endl;
    cin>> avg;
    cout <<"Worker(W) or Lazy(L) ir Responsible(R) Student?" <<endl;
    cin>> type;

    try{
        if (type =='L')
        {
            lazy_student* ls = new lazy_student(fn,ln,id,avg);
            this->all_students.push_back(ls);
        }

        else if (type =='W')
        {
            active_student* as = new active_student(fn,ln,id,avg);
            this->all_students.push_back(as);
        }

        else if (type =='R')
        {
            responsible_student* rs = new responsible_student(fn,ln,id,avg);
            this->all_students.push_back(rs);
        }
        else{
            throw invalidDetails();
        }
    }
    catch (exception& e){
        cout<<e.what()<<endl;
        return;
    }

}

void ZoomSys::assignStudent()
{
    int stu_id;
    int room_id;

    cout <<"---Assign Student---" <<endl;
    cout <<"Enter student id:" <<endl;
    cin>> stu_id;
    cout <<"Enter room id:" <<endl;
    cin>> room_id;


    try {
        Student *s = get_student_by_id(stu_id);
        //if (s->get_roomID() == room_id) { return; }
        //if (s->get_roomID() == room_id) { return; }
        if (room_id == -1) {
            if (s->get_room() != nullptr) {
                s->get_room()->remove_student(s);
            }
            return;
        } else {
            Room *r = get_room_by_id(room_id);
            if (s->get_room() != nullptr) {
                s->get_room()->remove_student(s);
            }
            r->add_student(s);
        }
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
        return;
    }


}

ZoomSys::~ZoomSys() {

    for (int i =0; i < all_students.size(); i++){
        delete all_students[i];
        all_students[i] = nullptr;
    }
    for (int i = 0; i < root_rooms.size(); i++){
        delete root_rooms[i];
        root_rooms[i] = nullptr;
    }

}


