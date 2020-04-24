/*IMPLEMENTATION OF Array CLASS*/
#include "../Headers/array.h"
#include "../Headers/globals.h"
#include <QPainter>
using std::string;

//Constructor
Array::Array(string n, string t, string e)
{
    name = n;
    type = t;
    elements = e;
}
//Method(s)
void Array::display(QPainter& painter, int mode)
{
    if(mode == 0)
    {
        painter.drawText(startingX_for_text, startingY_for_text, QString::fromStdString(name + "[]: " + type));

        return;
    }
    else if(mode == 1)
    {
        painter.drawText(startingX_for_text, startingY_for_text, QString::fromStdString(type + "[]"));

        return;
    }
}
