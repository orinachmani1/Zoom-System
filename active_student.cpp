#include "active_student.h"
#include "My_Exceptions.h"

active_student::active_student(string fn, string ls, int id, double average):
                            Student(fn,ls,id,average){}

void active_student::split_yourself(Room *r, Room* L, Room* R)
{
    r->remove_student(this);
    L->add_student(this);
}

void active_student::work_message()
{
    cout<< this->get_first_name()<< ' ' <<this->get_last_name() <<" is working"<<endl;
}

void active_student::send_message_to_class(string content)
{
    throw Student_permissions();
}
