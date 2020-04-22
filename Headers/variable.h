#ifndef VARIABLE_H
#define VARIABLE_H

/*CLASS DEFINITION FOR "Class" CLASS.*/
#include <vector>
#include <string>
#include <QPainter>

using std::vector;
using std::string;

class Variable
{
protected:
    /*Detected elements of a Variable*/
    string name;
    string type;
public:
    //Constructors
    Variable(){}
    Variable(string/*name*/, string/*type*/);
    QString ret_type();
    friend void search_class();
    virtual void display(QPainter& painter, int);
};
#endif // VARIABLE_H
