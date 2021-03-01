#include "Room.h"
#include "active_room.h"
#include "lazy_room.h"
#include "My_Exceptions.h"
#include<iterator>

int Room::roomsCounter = 0;

Room::Room()
{
    this->id = roomsCounter;
    roomsCounter++;
    this->num_of_students = 0;
    this->father = nullptr;
    this->Left = nullptr;
    this->Right = nullptr;
}

void Room::remove_student(Student* stu)
{

    vector<Student*>::iterator iter;
    for(iter = this->all_students.begin(); iter < all_students.end(); iter++)
    {
        if(*iter==stu)
        {
            this->all_students.erase(iter);
            break;
        }
    }
    stu->set_room(nullptr);
    stu->set_roomID(-1);
    num_of_students--;
}

void Room::add_student(Student* s)
{
    this->all_students.push_back(s);
    s->set_roomID(this->get_id());
    num_of_students++;
    s->set_room(this);
}

void Room::split_room_by_character()
{
    if (this->num_of_students <= 0){return;}

    Room* left = new active_room();
    Left = left;
    Left->father= this;

    Room* right = new lazy_room();
    Right = right;
    Right->father = this;

    vector<Student*>::iterator iter;
    vector<Student*> copy_of_students_in_room = this->all_students;
    for(iter = copy_of_students_in_room.begin(); iter < copy_of_students_in_room.end(); iter++)
    {
        (*iter)->split_yourself(this , left, right);
    }

}

void Room::split_room_by_quantity()
{
    int num_of_stu = this->get_num_of_students();
    if (num_of_stu <=0){return;}

    int num_to_left = num_of_stu/2;
    int cur_room_id = this->id;

    Room* standard_room1 = new Room();
    Left = standard_room1;
    Left->father= this;

    Room* standard_room2 = new Room();
    Right = standard_room2;
    Right->father= this;
    vector<Student*> copy_of_all_students = all_students;
    int orig_num_of_student = num_of_students;
    for (int i = 0; i < num_to_left; ++i)
    {
        remove_student(copy_of_all_students[i]);
        Left->add_student(copy_of_all_students[i]);
    }

    for (int j = num_to_left; j < orig_num_of_student; ++j)
    {
        remove_student(copy_of_all_students[j]);
        Right->add_student(copy_of_all_students[j]);
    }
    this->num_of_students=0;
    this->all_students.clear();
}

void Room::printRoom()
{
    cout<<"room id:" << this->id <<  ", students:" << this->num_of_students << endl;
//    if (nullptr != this->Left){
//        this->Left->printRoom();
//    }
//    if (nullptr != this->Right){
//        this->Right->printRoom();
//    }

}

void Room::print_students()
{
    for (int i = 0; i < all_students.size() ; ++i) {
        all_students[i]->printStudent();
    }

}

Room::~Room()
{
    delete this->Left;
    this->Left = nullptr;
    delete this->Right;
    this->Right = nullptr;

    if (this->father != nullptr){
        if (this->father->Left == this){
            this->father->Left = nullptr;
        }
        if (this->father->Right == this){
            this->father->Right = nullptr;
        }
    }


    //no leaves : no father = move to room -1
    //          : father = move to father's room


    vector<Student*>::iterator iter;

    vector<Student*> copy_of_all_students = all_students;

    if (this->Left == nullptr && this->Right == nullptr)
    {
        if (this->father == nullptr)
        {
            for(iter = copy_of_all_students.begin(); iter < copy_of_all_students.end(); iter++) {
                if (*iter != nullptr){
                    (*iter)->set_roomID(-1);
                    int id = (*iter)->get_id();
                    this->remove_student(*iter);
                    num_of_students--;
                    (*iter)->cry();
                }

            }
        }
        else
        {
            for(iter = copy_of_all_students.begin(); iter < copy_of_all_students.end(); iter++)
            {
                if (*iter != nullptr){
                    this->remove_student(*iter);
                    this->father->add_student(*iter);
                    num_of_students--;
                    (*iter)->cry();
                }

            }
        }
    }


}

void Room::removeRoom() {



}

void Room::remove_student(int id) {

    Student* to_remove = get_student_by_id(id);
    remove_student(to_remove);
}

Student *Room::get_student_by_id(int id) {
    vector<Student*>::iterator iter;
    for(iter = this->all_students.begin(); iter < all_students.end(); iter++) {
        if ((*iter)->get_id() == id ){
            return *iter;
        }
    }
    throw invalidID();

}

void Room::split_room(int split_type) {
    if (this->Left != nullptr || this->Right != nullptr){
        throw Split_before();
    }
    if (split_type==1)
    {
        this->split_room_by_character();
    }
    else if (split_type==2)
    {
        this->split_room_by_quantity();
    }
}
