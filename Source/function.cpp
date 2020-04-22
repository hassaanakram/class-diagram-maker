/*IMPLEMENTATION OF FUNCTION CLASS*/
#include "../Headers/function.h"
#include "../Headers/globals.h"
#include <QPainter>
using std::string;
using std::vector;

//Constructor
Function::Function(string n, string r_t, vector<Variable*>& param)
{
    name = n;
    return_type = r_t;

    //Parameters
    for (auto it = param.begin(); it != param.end(); it++)
    {
        parameters.push_back(*it);
    }
}
Function::Function(string n, string r_t)
{
    name = n;
    return_type = r_t;
}
//Method(s)
void Function::display(QPainter& painter)
{
    //To store the initial starting position for x to use on a new line
    int old_start_x = start_x;
    //Vector of QStrings to store the parameters
    vector<QString> params;
    //Resizing. As vector::push_back() was not working as expected
    params.resize(20);
    //Counter for the container
    size_t c = 0;
    //To be used as a flag
    bool move_down = false;
    //Accumulating the types of parameters in a QString
    for(auto itr = this->parameters.begin(); itr != this->parameters.end(); itr++)
    {
        if(params[c].length() >= 30)
        {
            c++;
        }
        if(itr != parameters.end() - 1)
        {
            params[c] = params[c] + (*itr)->ret_type() + ", ";
        }
        else {
            params[c] = params[c] + (*itr)->ret_type();
        }
    }
    //Shrinking the vector
    params.resize(c+1);
    //Means we need to have more than one lines
    if(c > 0)
        move_down = true;

    //Drawing here "function("
    painter.drawText(start_x, start_y, QString::fromStdString(name + "("));
    start_x += (name.length()) * 6 + 5;
    //Now for the parameters part
    for(auto itr = params.begin(); itr != params.end(); itr++)
    {
        painter.drawText(start_x, start_y, *itr);
        start_y += 15;
        start_x = old_start_x;
    }
    start_y -= 15;
    //Change start_x
    if(move_down)
    {
        start_x += ((params.back()).length()) * 6;
    }
    else
    {
        start_x += (name.length())*6;
        start_x += 5;
        start_x += (params[c].length())*6;
    }
    painter.drawText(start_x, start_y, "): " + QString::fromStdString(this->return_type));
    start_x = old_start_x;
    return;
}
