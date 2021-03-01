#ifndef ZOOM_MY_EXCEPTIONS_H
#define ZOOM_MY_EXCEPTIONS_H

#include <exception>
#include "ZoomSys.h"

using namespace std;


class invalidDetails: public exception
{
    virtual const char* what() const throw()
    {
        return "Please enter valid details";
    }

};

class invalidID: public exception
{
    virtual const char* what() const throw()
    {
        return "id doesn't exists";
    }

};

class Student_permissions: public exception
{
    virtual const char* what() const throw()
    {
        return "this student don't have permission";
    }

};

class Split_before: public exception
{
    virtual const char* what() const throw()
    {
        return "This room was split before";
    }

};

#endif //ZOOM_MY_EXCEPTIONS_H
