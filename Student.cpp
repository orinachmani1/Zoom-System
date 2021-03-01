#include "Student.h"
#include "My_Exceptions.h"

Student::Student(string fn, string ls, int id, double average)
{
    if (average > 100 || average < 0)
    {
        throw invalidDetails();
    }
    this->firstName = fn;
    this->lastName = ls;
    this->id = id;
    this->average = average;
    this->roomID = -1;
    this->myRoom = nullptr;
}


void Student::receiveMassage(message* m)
{
    message* my_message = new message(*m);
    this->messages.push_back(my_message);
}

void Student::print_all_messages()
{

    cout<< "---Messages---"<<endl;
    vector<message*>::iterator iter;
    for(iter = this->messages.begin(); iter < this->messages.end(); iter++)
    {
        (*iter)->printMessage();
    }

}

void Student::printStudent()
{
    cout<< this->firstName << ' ' << this->lastName << ' ' << this->id << ' ' << this->average << ' ' << this->roomID<< endl;
}

Student::~Student()
{
    vector<message*>::iterator iter;
    for(iter = this->messages.begin(); iter < this->messages.end(); iter++)
    {
        delete *iter;
    }
    if (myRoom!= nullptr){
        vector<Student*>::iterator iter;
        for (iter=(*(myRoom->get_students())).begin(); iter < (*(myRoom->get_students())).end(); iter++){
            if (*iter == this){
                (*(myRoom->get_students())).erase(iter);
                break;
            }
        }
    }

}