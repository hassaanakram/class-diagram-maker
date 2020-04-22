#ifndef CLASS_H
#define CLASS_H

/*CLASS DEFINITION FOR "Class" CLASS.*/
#include "variable.h"
#include "function.h"
#include "win_main.h"
#include <QPainter>
using std::vector;
using std::string;

class Class
{
private:
    /*Detected elements of a class*/
    string name;
    vector<Variable*> pvt_data_members;
    vector<Function*> pvt_member_functions;
    vector<Variable*> prot_data_members;
    vector<Function*> prot_member_functions;
    vector<Variable*> pub_data_members;
    vector<Function*> pub_member_functions; //Member functions include constructors
    vector<Function*> frnd_functions;
    vector<Function*> virtual_functions;
    vector<string> frnd_classes;
    bool inherited; /*Is it inherited BY somecalss or not?*/
    bool derived; /*is it derived from some base class or not?*/
    string base_class; /*If derived then the base class (currently no supporting multiple inheritence)*/
    vector<Class*> childs;
    int n_dchilds;
    int n_ichilds;
public:
    //Constructor
    Class(){}
    Class(string/*Name*/, vector<Variable*>&/*pvt*/, vector<Function*>&/*pvt*/, vector<Variable*>& prot_var, vector<Function*>& prot_fun, vector<Variable*>&/*pub*/, vector<Function*>&/*pub*/, vector<Function*>&/*frnd fun*/, vector<string>&/*frnd classes*/, vector<Function*>&/*virtual funs*/
          , string p = "", const Class* pb = nullptr);

    int get_dchilds();
    int get_ichilds();
    friend void search_inhclass();
    friend void print(Win_main *w);
    friend void print_IndepClasses(QPainter& painter);
    friend void print_InheritedClass(QPainter& painter, vector<Class>::iterator& itr);
    friend void print_InheritedClass(QPainter& painter, vector<Class*>::iterator& itr);
    virtual void display(QPainter& painter);
};

#endif // CLASS_H
