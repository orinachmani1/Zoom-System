#ifndef ZOOM_HW5_MESSAGE_H
#define ZOOM_HW5_MESSAGE_H

#include <string>
#include <iostream>
using namespace std;

class message {
public:
    string first;
    string last;
    string content;

    message(string fn,string ln,string cont ){this->first = fn;this->last = ln; this->content = cont; }
    message(const message &other){this->first = other.first; this->last = other.last; this->content = other.content;}
    ~message(){};
    void printMessage();
};


#endif //ZOOM_HW5_MESSAGE_H
