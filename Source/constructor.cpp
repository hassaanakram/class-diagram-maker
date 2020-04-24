/*Implementation of Constructor class*/
#include "../Headers/constructor.h"
#include "../Headers/globals.h"
#include  <QPainter>
using std::string;
using std::vector;

Constructor::Constructor(string n, vector<Variable*> param)
{
    name = n;
    //Feeding parameters
    for (auto it = param.begin(); it != param.end(); it++)
    {
        parameters.push_back(*it);
    }
}
Constructor::Constructor(string n)
{
    name = n;
}
//Method(s)
void Constructor::display(QPainter& painter)
{
    //To store the initial starting position for x to use on a new line
    int old_startingX_for_text = startingX_for_text;
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
    painter.drawText(startingX_for_text, startingY_for_text, QString::fromStdString(name + "("));
    startingX_for_text += (name.length()) * 6 + 5;
    //Now for the parameters part
    for(auto itr = params.begin(); itr != params.end(); itr++)
    {
        painter.drawText(startingX_for_text, startingY_for_text, *itr);
        startingY_for_text += 15;
        startingX_for_text = old_startingX_for_text;
    }
    startingY_for_text -= 15;
    //Change startingX_for_text
    if(move_down)
    {
        startingX_for_text += ((params.back()).length())*6;
    }
    else
    {
        startingX_for_text += (name.length())*6;
        startingX_for_text += 5;
        startingX_for_text += (params[c].length())*6;
    }
    painter.drawText(startingX_for_text, startingY_for_text, ")");
    startingX_for_text = old_startingX_for_text;
    return;
}
