/*IMPLEMENTATION OF Class CLASS*/
#include "../Headers/class.h"
#include "../Headers/globals.h"
#include <QString>
#include <QFileDialog>
#include <QPainter>

using std::string;
using std::vector;

//Constructor
Class::Class(string n, vector<Variable*>& pvt_var, vector<Function*>& pvt_fun,
            vector<Variable*>& prot_var, vector<Function*>& prot_fun,
            vector<Variable*>& pub_var, vector<Function*>& pub_fun,
            vector<Function*>& f_fun, vector<string>& f_cls,
            vector<Function*>& v_fun
            , string p, const Class* pb)
{
    name = n;
    inherited = false;
    derived = false;
    n_dchilds = 0;
    n_ichilds = 0;

    //Feeding private variables
    for (auto it = pvt_var.begin(); it != pvt_var.end(); it++)
    {
        pvt_data_members.push_back(*it);
    }
    //Feeding public variables
    for (auto it = pub_var.begin(); it != pub_var.end(); it++)
    {
        pub_data_members.push_back(*it);
    }
    //Feeding protected variables
    for (auto it = prot_var.begin(); it != prot_var.end(); it++)
    {
        prot_data_members.push_back(*it);
    }
    //Feeding private functions
    for (auto it = pvt_fun.begin(); it != pvt_fun.end(); it++)
    {
        pvt_member_functions.push_back(*it);
    }
    //Feeding protected functions
    for (auto it = prot_fun.begin(); it != prot_fun.end(); it++)
    {
        prot_member_functions.push_back(*it);
    }
    //Feeding public functions
    for (auto it = pub_fun.begin(); it != pub_fun.end(); it++)
    {
        pub_member_functions.push_back(*it);
    }
    //Feeding friend functions
    for (auto it = f_fun.begin(); it != f_fun.end(); it++)
    {
        frnd_functions.push_back(*it);
    }
    //Feeding friend classes
    for (auto it = f_cls.begin(); it != f_cls.end(); it++)
    {
        frnd_classes.push_back(*it);
    }
    //Feeding virtual functions
    for (auto it = v_fun.begin(); it != v_fun.end(); it++)
    {
        virtual_functions.push_back(*it);
    }
}
//Method(s)
void Class::display(QPainter& painter)
{
     //Drawing will be done here

         //Printing name of class
         painter.drawText(start_x, start_y, QString::fromStdString(name));
         start_y += 10;
         painter.drawRect(x1,start_y,box_width,1); //Separtation line
         //painter.drawLine(x1,start_y,box_width,start_y);
         start_y += 15;

         if(pvt_data_members.size() > 0 || pub_data_members.size() > 0 || prot_data_members.size() > 0)
         {
            //Printing attributes first public, then pvt, then protected
            for(auto it = pvt_data_members.begin(); it != pvt_data_members.end(); it++)
            {
                painter.drawText(start_x, start_y, "-");
                start_x += 10;
                (*it)->display(painter, 0);
                start_x -= 10;
                start_y += 10;
            }
            for(auto it = pub_data_members.begin(); it != pub_data_members.end(); it++)
            {
                painter.drawText(start_x, start_y, "+");
                start_x += 10;
                (*it)->display(painter, 0);
                start_x -= 10;
                start_y += 10;
            }
            for(auto it = prot_data_members.begin(); it != prot_data_members.end(); it++)
            {
                painter.drawText(start_x, start_y, "#");
                start_x += 10;
                (*it)->display(painter, 0);
                start_x -= 10;
                start_y += 10;
            }

            //Separation line
            painter.drawRect(x1,start_y,box_width,1);
            start_y += 15;
         }
         if(pvt_member_functions.size() > 0 || pub_member_functions.size() > 0 ||  prot_member_functions.size() > 0
                 || frnd_functions.size() > 0 || virtual_functions.size()  > 0)
         {
            //Printing Methods (private, public, protected)
            for(auto it = pvt_member_functions.begin(); it != pvt_member_functions.end(); it++)
           {
                painter.drawText(start_x, start_y, "-");
                start_x += 10;
                (*it)->display(painter);
                start_y += 10;
                start_x -= 10;
            }
            for(auto it = pub_member_functions.begin(); it != pub_member_functions.end(); it++)
            {
                painter.drawText(start_x, start_y, "+");
                start_x += 10;
                (*it)->display(painter);
                start_x -= 10;
                start_y += 10;
            }
            for(auto it = prot_member_functions.begin(); it != prot_member_functions.end(); it++)
            {
                painter.drawText(start_x, start_y, "#");
                start_x += 10;
                (*it)->display(painter);
                start_x -= 10;
                start_y += 10;
            }
            for(auto it = virtual_functions.begin(); it != virtual_functions.end(); it++)
            {
                painter.drawText(start_x, start_y, "virtual ");
                start_x += 40;
                (*it)->display(painter);
                start_x -= 40;
                start_y += 10;
            }
            for(auto it = frnd_functions.begin(); it != frnd_functions.end(); it++)
            {
                painter.drawText(start_x, start_y, "friend ");
                start_x += 40;
                (*it)->display(painter);
                start_x -= 40;
                start_y += 10;
            }
         }

         //Drawing the box
         painter.drawRect(x1,y1,box_width,start_y - y1);

}
int Class::get_dchilds()
{
    for(auto itr = this->childs.begin(); itr != this->childs.end(); itr++)
    {
        if((*itr)->derived == true && (*itr)->inherited == false)
        {
            n_dchilds++;
        }
    }

    return n_dchilds;
}
int Class::get_ichilds()
{
    for(auto itr = this->childs.begin(); itr != this->childs.end(); itr++)
    {
        if((*itr)->derived == true && (*itr)->inherited == true)
        {
            n_ichilds++;
        }
    }

    return n_ichilds;
}
