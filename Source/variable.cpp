/*IMPLEMENTATION OF VARIABLE CLASS*/
#include "../Headers/variable.h"
#include "../Headers/globals.h"
#include <QPainter>

Variable::Variable(string n, string t)
{
    name = n;
    type = t;
}
QString Variable::ret_type()
{
    return (QString::fromStdString(type));
}
//Method(s)
void Variable::display(QPainter& painter, int mode)
{
    if(mode == 0)
    {
        //Drawing start
        painter.drawText(startingX_for_text, startingY_for_text, QString::fromStdString(name + ": " + type));

        return;
    }
    else if(mode == 1)
    {
        painter.drawText(startingX_for_text, startingY_for_text, QString::fromStdString(type));

        return;
    }

}
