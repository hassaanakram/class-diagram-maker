#ifndef GLOBALS_H
#define GLOBALS_H
//Native Libraries
#include <fstream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
#include <windows.h>
//Custom built
#include "class.h"
#include "variable.h"
#include "function.h"
#include "constructor.h"
#include "array.h"
#include "container.h"
#include "win_main.h"

//Qt
#include <QtSvg/QSvgGenerator>

using std::vector;
using std::string;

    extern QSvgGenerator temp_img;
    //extern QImage final_img;

    extern int x_space;
    extern int y_space;
    extern int x1_base;
    extern int y1_base;
    extern int start_x_base;
    extern int start_y_base;
    extern int prev_x;
    extern int i;
    extern int row;
    extern int prev_ry;
    extern int box_height;
    extern int box_width;
    extern int x1;
    extern int y1;
    extern int start_x;
    extern int start_y;
    extern int longest_y;
    extern int longest_x;
    extern int least_x;

    extern int f_y;
    extern vector<string> tokens; //VECTOR TO STORE TOKENS. EACH TOKEN IS OF TYPE STRING
    extern vector<char> buffer; //To store input from file into a local storage.

    extern vector<Class> classes; //Classes
    extern vector<Function> fun; //Non-member functions

    //Data types it increases in functionality as more and more data types are detected. Also, pointers are treated as datatypes
    extern vector<string> data_types;
    extern vector<string> containers;
    extern vector<string> dtype_containers;

    //Functions
    extern void print(Win_main *w); //Final results
    extern void print_IndepClasses(QPainter& painter);
    extern void print_InheritedClass(QPainter& painter, vector<Class>::iterator& itr);
    extern void print_InheritedClass(QPainter& painter, vector<Class*>::iterator& itr);
    extern void drawFork(QPainter& painter, const int& mode);
    extern void drawArrow(QPainter& painter, int mode);
    extern void drawILine(QPainter& painter, int mode);
    extern void set_space(const string& mode);
    extern void extract_chars(std::ifstream& input);
    extern void commence(Win_main *w);
    extern void remove_comments();
    extern void extract_tokens();  //To extract tokens
    extern void eat_spaces(); //Eat away any whitespaces from the tokens vector
    extern void eat_newlines();
    extern void combine(); //Combine } and ;  for easier detection of class definition end
    extern void parse(); //The playmaker!
    extern void search_class(); //To search for classes -> After class is found, use the search_var() and search_fun() functions
    extern void search_inhclass(); //To search for inheritd clsses. After base classes
    extern void search_param(vector<string>::iterator&/*Start*/, const vector<string>&, vector<Variable*>&);//To search from the starting iterator until any of the words in vector is encountered
    extern bool search_var(vector<string>::iterator&, vector<Variable*>&);//Search once
    extern bool search_fun(vector<string>::iterator&, vector<Function*>&); //Search once
    extern bool search_arr(vector<string>::iterator&, vector<Variable*>&); //Search once
    extern bool search_container(vector<string>::iterator&, vector<Variable*>&);//Search once
    extern bool search_frnd(vector<string>::iterator&, vector<string>&, vector<Function*>&); //To search for friends of a class
    extern bool search_vfun(vector<string>::iterator&, vector<Function*>&); //To search for virtual functions
    extern bool search_const(vector<string>::iterator&, vector<Function*>&, string); //To search for constructors
    extern void update_datatypes();
    //bool search_dest(vector<string>::iterator&, vector<Function>*&); //To search for destructors
    extern inline bool digit(char);
    extern inline bool letter(char);
    extern inline bool underscore(char);
    extern bool match(const vector<string>&, const vector<string>::iterator&);
    extern bool access_change(vector<string>::iterator&, string*);
    extern void  copy(int/*From*/, int/*To*/); //To copy token into the tokens vector
    extern void copy(vector<string>::iterator&, vector<string>::iterator&, string&);
#endif // GLOBALS_H
