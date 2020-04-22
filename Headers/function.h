#ifndef FUNCTION_H
#define FUNCTION_H

/*CLASS DEFINITION FOR "Function" CLASS.*/
#include "variable.h"

using std::vector;
using std::string;

class Function
{
private:
    string return_type;
protected:
    /*Detected elements of a Function*/
    string name;
    vector<Variable*> parameters;
public:
    //Constructor
    Function(){}
    Function(string/*name*/, string/*return type*/, vector<Variable*>&/*Parameters*/);
    Function(string/*name*/, string/*return type*/); //No argument functions

    virtual void display(QPainter& painter);
};
#endif // FUNCTION_H
