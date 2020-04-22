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
        painter.drawText(start_x, start_y, QString::fromStdString(name + "[]: " + type));

        return;
    }
    else if(mode == 1)
    {
        painter.drawText(start_x, start_y, QString::fromStdString(type + "[]"));

        return;
    }
}
