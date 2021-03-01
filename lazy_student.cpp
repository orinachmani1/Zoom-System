#include "lazy_student.h"
#include "My_Exceptions.h"

lazy_student::lazy_student(string fn, string ls, int id, double average):
        Student(fn,ls,id,average){}

void lazy_student::work_message()
{

}

void lazy_student::split_yourself(Room *r, Room *L, Room *R)
{
    r->remove_student(this);
    R->add_student(this);
}

void lazy_student::send_message_to_class(string content)
{
    throw Student_permissions();
}

void lazy_student::cry() {
    cout<< this->get_first_name()<< ' ' <<this->get_last_name() <<" is crying"<<endl;
}
