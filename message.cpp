#include "message.h"

void message::printMessage()
{
    cout<< this->first << ' ' << this->last << ":" << this->content<< endl;
}