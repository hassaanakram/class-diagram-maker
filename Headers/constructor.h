#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "function.h"
#include "variable.h"

using std::string;
using std::vector;

/*Constructor  Class definition*/
class Constructor : public Function
{
public:
    Constructor(string, vector<Variable*>);
    Constructor(string);
    virtual void display(QPainter& painter);
};

#endif // CONSTRUCTOR_H
