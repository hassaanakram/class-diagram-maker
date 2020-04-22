#ifndef ARRAY_H
#define ARRAY_H

/*CLASS DEFINITION FOR "Class" Array.*/
#include <vector>
#include <string>
#include "variable.h"

using std::vector;
using std::string;

class Array : public Variable
{
private:
    /*Detected elements of a Array. Name and type inherited from variable*/
    string elements;
public:
    //Constructors
     Array() {}
    Array(string/*name*/, string/*type*/, string/*elements*/);

    friend void search_class();
    virtual void display(QPainter& painter, int);
};
#endif // ARRAY_H
