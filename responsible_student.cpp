#include "responsible_student.h"
#include "message.h"

responsible_student::responsible_student(string fn, string ls, int id, double average):
        Student(fn,ls,id,average){}

void responsible_student::send_message_to_class(string content)
{
    if (this->get_room()== nullptr)
    {
        return;
    }
    message* m = new message(this->get_first_name(), this->get_last_name() , content);

    vector<Student*>::iterator iter;
    for(iter = (*(this->get_room()->get_students())).begin(); iter < (*(this->get_room()->get_students())).end(); iter++)
    {
        (*iter)->receiveMassage(m);
    }
    delete m;
}

void responsible_student::split_yourself(Room *r, Room* L, Room* R)
{

}

void responsible_student::work_message()
{

}