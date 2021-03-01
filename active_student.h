#ifndef EX5_ACTIVE_STUDENT_H
#define EX5_ACTIVE_STUDENT_H

#include "Student.h"
using namespace std;

class active_student: public Student {

public:
    active_student(string fn, string ls, int id, double average);
    virtual ~active_student(){};
    virtual void split_yourself(Room *r, Room* L, Room* R);
    virtual void work_message();
    virtual void send_message_to_class(string content);
    virtual void cry(){};
};


#endif //EX5_ACTIVE_STUDENT_H
