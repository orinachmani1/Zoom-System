#ifndef EX5_RESPONSIBLE_STUDENT_H
#define EX5_RESPONSIBLE_STUDENT_H

#include "Student.h"
class responsible_student: public Student {
public:
    responsible_student(string fn, string ls, int id, double average);
    virtual ~responsible_student(){};
    virtual void send_message_to_class(string content);
    virtual void split_yourself(Room *r, Room* L, Room* R);
    virtual void work_message();
    virtual void cry(){};
};


#endif //EX5_RESPONSIBLE_STUDENT_H
