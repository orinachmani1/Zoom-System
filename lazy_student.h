#ifndef EX5_LAZY_STUDENT_H
#define EX5_LAZY_STUDENT_H

#include "Student.h"

class lazy_student :public Student {

public:
    lazy_student(string fn, string ls, int id, double average);
    virtual ~lazy_student(){};
    virtual void split_yourself(Room *r, Room* L, Room* R);
    virtual void work_message();
    virtual void send_message_to_class(string content);
    virtual void cry();
};


#endif