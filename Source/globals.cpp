#include "../Headers/globals.h"
#include <QDialog>
#include <QFileDialog>
#include <QPainter>
#include <QFont>
#include <QSize>
#include <QRect>
#include <QPolygon>
#include <QPoint>
#include <QLineF>
#include <QMessageBox>

using namespace std;

//Data
QSvgGenerator temp_img;
int x_space = 40;
int y_space = 30;
int row = 0;
int x1_base = 0;
int y1_base = 0;
int start_x_base = 0;
int start_y_base = 0;
int box_width = 300;
int x1 = 20;
int y1 = 20;
int start_x = 30;
int start_y = 30;
int longest_y = 0;
int longest_x = 0;
int least_x = 0;
int f_y = 0;
int prev_ry = 0;
int prev_x = 0;
int i = 0;

vector<string> tokens = {};
vector<char> buffer = {};

vector<Class> classes ={};
vector<Function> fun ={};
vector<string> data_types = { "QString", "string", "void","bool", "int", "float", "double", "char", "wchar_t", "size_t", "QPainter", };
vector<string> containers = { "vector", "list", "deque", "array", "map" };
vector<string> dtype_containers = {};

/*------------------------------FUNCTION DEFINITIONS-----------------------------------*/
void drawFork(QPainter& painter, const int& mode)
{
    static int prev_x1 = 0;
    static int prev_y1 = 0;
    static int prev_start_x = 0;
    static int prev_start_y = 0;
    if(mode == 0)
    {
        QLineF *lines = new QLineF[2];

        lines[0].setP1(QPoint(x1-10, y1 - y_space - (start_y - y1)/2));
        lines[0].setP2(QPoint(x1 - 10, y1+(start_y - y1)/2));

        lines[1].setP1(QPoint(x1 - 10, y1 + (start_y - y1)/2));
        lines[1].setP2(QPoint(x1, y1+(start_y - y1)/2));

        painter.setPen(Qt::red);
        painter.drawLines(lines, 2);
        painter.setPen(Qt::black);

        if(i == 2)
        {
            prev_x1 = x1;
            prev_y1 = y1;
            prev_start_x = x1 + 10;
            prev_start_y = y1 + 10;
        }

        delete[] lines;
    }
    else if(mode == 1)
    {
        QLineF *lines = new QLineF[2];

        lines[0].setP1(QPoint(prev_x1-10, prev_y1 - y_space - (prev_start_y - y1)/2));
        lines[0].setP2(QPoint(prev_x1 - 10, prev_y1+(prev_start_y - prev_y1)/2));

        lines[1].setP1(QPoint(prev_x1 - 10, prev_y1 + (prev_start_y - prev_y1)/2));
        lines[1].setP2(QPoint(prev_x1, prev_y1+(prev_start_y - prev_y1)/2));

        painter.setPen(Qt::red);
        painter.drawLines(lines, 2);
        painter.setPen(Qt::black);

    }
    return;
}
void drawArrow(QPainter& painter, int mode/*to specify direction*/)
{
    if(mode == 0) //Mode 0 signifies that the arrow is to be drawn at the bottom edge of the box ie for
                  //displaying non-inherited childs
    {
        //Defining points
        QPoint *points = new QPoint[4];
        points[0].setX(x1 + box_width/2);
        points[0].setY(start_y);

        points[1].setX(x1 + box_width/2 - 5);
        points[1].setY(start_y + 5);

        points[2].setX(x1 + box_width/2 + 5);
        points[2].setY(start_y + 5);

        points[3].setX(x1 + box_width/2);
        points[3].setY(start_y);

        //Set coords for further use
        x1_base = x1;
        y1_base = y1;
        start_x_base = start_x;
        start_y_base = start_y;
        painter.setPen(Qt::red);
        painter.drawPolyline(points, 4);
        painter.setPen(Qt::black);
        return;
    }
    else if(mode == 1) //Mode 1 is to indicate that the arrow is to be drawn at the upper edge
                       //that is for the childs that are inherited further
    {
        //Defining points
        QPoint *points = new QPoint[4];
        points[0].setX(x1 + box_width/2 + 10);
        points[0].setY(y1);

        points[1].setX(x1 + box_width/2 - 5 + 10);
        points[1].setY(y1 - 5);

        points[2].setX(x1 + box_width/2 + 5 + 10);
        points[2].setY(y1 - 5);

        points[3].setX(x1 + box_width/2 + 10);
        points[3].setY(y1);

        //Set coords for further use
        x1_base = x1;
        y1_base = y1;
        start_x_base = start_x;
        start_y_base = start_y;

        painter.setPen(Qt::red);
        painter.drawPolyline(points, 4);
        painter.setPen(Qt::black);
        return;
    }
}
void drawILine(QPainter& painter, int mode)
{
    //Now the lines
    if(mode == 0)
    {
        QLineF *lines = new QLineF[3];
        lines[0].setP1(QPoint(x1_base + box_width/2, start_y_base+ 5));
        lines[0].setP2(QPoint(x1 - 10, y1));

        lines[1].setP1(QPoint(x1 - 10, y1));
        lines[1].setP2(QPoint(x1 - 10, y1 + (start_y - y1)/2));

        lines[2].setP1(QPoint(x1 - 10, y1 + (start_y - y1)/2));
        lines[2].setP2(QPoint(x1, y1 + (start_y - y1)/2));

        painter.setPen(Qt::red);
        painter.drawLines(lines, 3);
        painter.setPen(Qt::black);
        return;
    }
    else if(mode == 1)
    {
        QLineF *lines = new QLineF[3];
        lines[0].setP1(QPoint(x1_base + box_width/2 + 10, y1_base - 5));
        lines[0].setP2(QPoint(x1_base + box_width/2 + 10, y1_base - 20));

        lines[1].setP1(QPoint(x1_base + box_width/2 + 10, y1_base - 20));
        lines[1].setP2(QPoint(x1 + box_width/2, y1_base - 20));

        lines[2].setP1(QPoint(x1 + box_width/2, y1_base - 20));
        lines[2].setP2(QPoint(x1 + box_width/2, y1));

        painter.setPen(Qt::red);
        painter.drawLines(lines, 3);
        painter.setPen(Qt::black);
        return;
    }
}
void set_space(const string& mode)
{
    //Setting display coordss etc

    if(mode == "non-inherited")
    {
        if(start_y > longest_y)
        longest_y = start_y;
        if(start_y > f_y)
            f_y = start_y;
        if(x1 > longest_x)
            longest_x = x1;

        if(i % 3 == 0)
        {
            //For next class
            f_y = start_y;
            prev_ry = start_y;
            start_y = longest_y + y_space;
            start_x = 30;
            x1 = start_x - 10;
            y1 = start_y - 10;
        }
        else
        {
           //Now reverting coordinates for the next class
           f_y = start_y;
           start_x = x1 + box_width + x_space;
           start_y = prev_ry  + y_space;
           x1 += box_width + (x_space - 10);
           y1 = start_y - 10;
        }
    }

    else if(mode == "inherited")
    {
        if(start_y > longest_y)
        longest_y = start_y;
        if(start_y > f_y)
            f_y = start_y;
        if(x1 > longest_x)
            longest_x = x1;

        if(i % 3 == 0)
        {
            //For next row
            row++;
            i = 0;
            //prev_ry = start_y;
            f_y = start_y;
            start_y = longest_y + y_space;
            start_x = 30;
            x1 = start_x - 10;
            y1 = start_y - 10;
        }
        else
        {
           //Now reverting coordinates for the next class
           f_y = start_y;
           start_y = y1 + 10;
           start_x = x1 + box_width + x_space;
           x1 += box_width + (x_space - 10);
           y1 = start_y - 10;
        }
    }
    else if(mode == "inherited-child")
    {
        if(start_y > longest_y)
        longest_y = start_y;
        if(start_y > f_y)
            f_y = start_y;
        if(x1 > longest_x)
            longest_x = x1;
        if(i == 1)
            least_x = x1;

        if(i % 3 == 0)
        {
            //For next row
            row++;
            i = 0;
            //prev_ry = start_y;
            f_y = start_y;
            start_y = longest_y + y_space;
            start_x = least_x + 10;
            x1 = start_x - 10;
            y1 = start_y - 10;
        }
        else
        {
           //Now reverting coordinates for the next class
           f_y = start_y;
           start_y = y1 + 10;
           start_x = x1 + box_width + x_space;
           x1 += box_width + (x_space - 10);
           y1 = start_y - 10;
        }
    }
    else if(mode == "three")
    {
        start_x = 30;
        x1 = start_x - 10;
        start_y += 70;
        y1 = start_y - 10;
    }
    else if(mode == "two")
    {
        start_x = (x_space-10) + box_width/2;
        x1 = start_x - 10;
        start_y += 70;
        y1 = start_y - 10;
    }
    else if(mode == "one")
    {
        start_x = x1 + 10;
        x1 = start_x - 10;
        start_y += 70;
        y1 = start_y - 10;
    }
    else if(mode == "three-child")
    {
        start_x = longest_x + box_width + x_space;
        x1 = start_x - 10;
        start_y += 90;
        y1 = start_y - 10;
    }
    else if(mode == "two-child")
    {
        start_x = longest_x + x_space + box_width/2 + box_width + x_space;
        x1 = start_x - 10;
        start_y += 90;
        y1 = start_y - 10;
    }
    else if(mode == "one-child")
    {
        start_x = x1_base + 10;
        x1 = start_x - 10;
        start_y += 90;
        y1 = start_y - 10;
    }
}
void commence(Win_main *w)
{
    classes.reserve(20);
    extract_tokens();
    eat_spaces();
    remove_comments();
    eat_newlines();
    update_datatypes();
    combine();
    parse();
    print(w);
}
void print_IndepClasses(QPainter& painter)
{
    QMessageBox alert;

    //Iterator
    vector<Class>::iterator itr = classes.begin();

    while(itr != classes.end())
    {
        if(!(itr->inherited) && !(itr->derived))
        {
            itr->display(painter);
            prev_x = x1;
            i++;

            set_space("non-inherited");
            itr++;
        }
        else
        {
            itr++;
        }
    }

    return;
}
void print_InheritedClass(QPainter& painter, vector<Class>::iterator& itr)
{
    QMessageBox alert;

    //Initializations
    row = 0;
    prev_ry = y1 - 10;

    //Print Base class
    itr->display(painter);
    //Coord update
    prev_x = x1;
    //Draw arrow head. Coords of the base class are saved in drawArrow()
    drawArrow(painter, 0);

    //Get number of childs
    int n_dchilds = itr->get_dchilds();
    int n_ichilds = itr->get_ichilds();

    //Print non-inherited childs of the class in question
    {
        //Iterator
        vector<Class*>::iterator it = itr->childs.begin();

        //First row
        row++;
        //The count of element in the current row
        i = 0;
        //NOW ONTO DISPLAYING THE Non inherited childs
        if(n_dchilds >= 3)
        {
            set_space("three");
            while(it != itr->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                     set_space("inherited");
                     it = itr->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }

            }
        }
        else if(n_dchilds == 2)
        {
            set_space("two");
            while(it != itr->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                    set_space("inherited");
                    it = itr->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }
            }
        }
        else if(n_dchilds == 1)
        {
            set_space("one");
            while(it != itr->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                    set_space("inherited");
                    it = itr->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }
            }
        }
    }
    //Now to print the childs that are inherited further
    x1 = x1_base;
    y1 = y1_base;
    start_x = x1 + 10;
    start_y = y1 + 10;

    {
        vector<Class*>::iterator it = itr->childs.begin();
        if(n_ichilds > 0)
        {
            //Print the arrow head
            drawArrow(painter, 1);
            //Move left
            x1 = longest_x + 2*box_width + x_space - 30 + x_space;
            start_x = x1 + 10;
            while(it != itr->childs.end())
            {
                //Now, printing this child as a 'Inherited class'
                if((*it)->derived && (*it)->inherited)
                {
                    print_InheritedClass(painter, it);
                    it = itr->childs.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
    return;
}
void print_InheritedClass(QPainter& painter, vector<Class*>::iterator& itr)
{
    QMessageBox alert;

    //Initializations
    row = 0;
    prev_ry = y1 - 10;

    //Print Base class
    (*itr)->display(painter);
    //Coord updateZ
    prev_x = x1;
    //Draw arrow head and line from base to this child. Coords of the base class are saved in drawArrow()
    drawILine(painter, 1);
    drawArrow(painter, 0);

    //Get number of childs
    int n_dchilds = (*itr)->get_dchilds();
    int n_ichilds = (*itr)->get_ichilds();

    //alert.setText("DCHILDS FOR " + QString::fromStdString((*itr)->name) + " " + QString::number(n_dchilds));
    //alert.exec();
    //alert.setText("ICHILDS FOR " + QString::fromStdString((*itr)->name) + " " + QString::number(n_ichilds));
    //alert.exec();

    //Print non-inherited childs of the class in question
    {
        //Iterator
        vector<Class*>::iterator it = (*itr)->childs.begin();

        //First row
        row++;
        //The count of element in the current row
        i = 0;
        //NOW ONTO DISPLAYING THE Non inherited childs
        if(n_dchilds >= 3)
        {
            set_space("three-child");
            while(it != (*itr)->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                     set_space("inherited-child");
                     it = (*itr)->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }

            }
        }
        else if(n_dchilds == 2)
        {
            set_space("two-child");
            while(it != (*itr)->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                    set_space("inherited-child");
                    it = (*itr)->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }
            }
        }
        else if(n_dchilds == 1)
        {
            set_space("one-child");
            while(it != (*itr)->childs.end())
            {
                if(!((*it)->inherited))
                {
                    (*it)->display(painter);
                    prev_x = x1;
                    i++;
                    if(row == 1)
                        drawILine(painter, 0);
                    else if(row > 1)
                        drawFork(painter, 0);

                    set_space("inherited-child");
                    it = (*itr)->childs.erase(it);
                 }
                 else
                 {
                    it++;
                 }
            }
        }
    }
    //Now to print the childs that are inherited further
    x1 = x1_base;
    y1 = y1_base;
    start_x = x1 + 10;
    start_y = y1 + 10;

    //alert.setText("Now for inherited childs of " + QString::fromStdString((*itr)->name));
    //alert.exec();
    {
        vector<Class*>::iterator it = (*itr)->childs.begin();
        if(n_ichilds > 0)
        {
            //Print the arrow head
            drawArrow(painter, 1);
            //Move left
            x1 += 3*box_width + 20 + 2*x_space;
            start_x = x1 + 10;
            while(it != (*itr)->childs.end())
            {
                //Now, printing this child as a 'Inherited class'
                if((*it)->derived && (*it)->inherited)
                {
                    print_InheritedClass(painter, it);
                    it = (*itr)->childs.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }

    return;
}

void print(Win_main  *w)
{
    QMessageBox alert;

    //Iterators
    vector<Class>::iterator itr = classes.begin();

    //Save file as SVG
    QString path = QFileDialog::getSaveFileName(w, ("Save as image"), "", ("SVG file (*.svg)"));
    //QString path = "C://users/moham/desktop/uml2.svg";
    if (path.isEmpty())
        return;

    temp_img.setFileName(path);

    //Painter settings
    QPainter painter;
    painter.begin(&temp_img);
    painter.setFont(QFont("Arial",24));

    /*Printing heading*/
    painter.drawText(20, 7, "CLASS DIAGRAMS. Made Using UML Creator");

    //FIRST WAVE FOR CLASSES WITHOUT ANY INHERITANCE RELATIONS
    painter.setFont(QFont("Arial", 12));

    print_IndepClasses(painter);

    //SECOND WAVE FOR INHERITENCE BOUND CLASSES
    itr =  classes.begin();
    while(itr != classes.end())
    {
        //FORMATTING
        start_y = longest_y + 100; //MOVE DOWN
        start_x = box_width + ((x_space - 10) * 2); //ALONG HORIZONTAL
        y1 = start_y - 10;
        x1 = start_x - 10;

        //CHECK FOR CLASSES THAT ARE INHERITED BUT NOT DERIVED
        if((itr->inherited) && !(itr->derived))
        {            
            print_InheritedClass(painter, itr);

            itr++;
    }
    else
        {
            itr++;
        }
    }
    painter.end();
}
void extract_chars(std::ifstream& input)
{
    char temp = '\0';
    while (input.get(temp))
    {
        buffer.push_back(temp);
    }
    //Append a null character at the end
    buffer.push_back('\0');

    return;
}
void remove_comments()
{
    for(auto itr = tokens.begin(); itr != tokens.end(); itr++)
    {
        //Multiple lines comment
        if(*itr == "/" && *(itr+1) == "*")
        {
            itr = tokens.erase(itr); //Remove '/'
            itr = tokens.erase(itr); //Remove '*'

            while(*itr != "*")
            {
                itr = tokens.erase(itr);
            }
            //Now itr is pointing to a '*'
            itr = tokens.erase(itr);
            //Now pointing to a '/'
            itr = tokens.erase(itr);
            itr--;
        }
        //Single line comment
        else if(*itr == "/" && *(itr + 1) == "/")
        {
            //Remove the '//'
            itr = tokens.erase(itr);
            itr = tokens.erase(itr);

            while(*itr != "\n")
            {
                itr = tokens.erase(itr);
            }
            //New line character will be removed in the eat_spaces() function
        }
    }
}
void extract_tokens()
{
    std::size_t i = 0; //Counter

    /*ALGORITHM:
      1 - Start to go through the buffer
      2 - Whenever a whitespace or any special character (other than underscore and a digit before a
          whitespace) is encountered, a token is complete.
      3 - Store the token in a vector of strings
      */

    while (buffer[i] != '\0')
    {
        if (!digit(buffer[i]) && !letter(buffer[i]) && !underscore(buffer[i]))
        {
            //Means a token is complete now going back to the start of the token
            int j = i-1;
            while (j > -1 && (digit(buffer[j]) || letter(buffer[j]) || underscore(buffer[j])))
            {
                //Not done yet keep going back
                j--;
            }
            //Went back completely. Actually one more than required so,
            copy(j + 1, i - 1); //Token copied to vector tokens
            copy(i, i); //The current character is a token too
        }
        //Increment counter
        i++;
    }

    //Done
    return;
}
void eat_spaces()
{
    vector<string>::iterator it = tokens.begin();

    while(it != tokens.end())
    {
        if ((*it)[0] == ' ' || *it == "" || *it == " " || *it == "\t")
        {
            it = tokens.erase(it);
        }
        else
            it++;
    }

    return;
}
void eat_newlines()
{
    vector<string>::iterator it = tokens.begin();

    while(it != tokens.end())
    {
        if ((*it)[0] == '\n')
        {
            it = tokens.erase(it);
        }
        else
            it++;
    }

    return;
}
void update_datatypes()
{
    vector<string>::iterator it = tokens.begin();

    for (; it != tokens.end(); it++)
    {
        if ((*it == "class" && *(it + 2) == "{") || (*it == "class" && *(it + 2) == ";")) //class abc {   OR class abc;
        {
            data_types.push_back(*(it + 1));
        }
    }
}
void combine()
{
    vector<string>::iterator it = tokens.begin();

    while (it != tokens.end())
    {
        if (*it == "}" && *(it + 1) == ";")
        {
            *it = (*it) + *(it + 1);
            it = tokens.erase(it + 1);
        }
        else if (*it == "." && regex_match(*(it + 1), regex("[0-9]+")) && regex_match(*(it-1), regex("[0-9]+")))
        {
            *(it-1) = (*(it - 1)) + (*it) + (*(it + 1));
            it = tokens.erase(it);
            it = tokens.erase(it);
        }
        else if (*it == "."  && regex_match(*(it + 1), regex("[0-9]+")))
        {
            *it = (*it) + (*(it + 1));
            it = tokens.erase(it + 1);
        }
        else if ((*it == "'" && *(it + 2) == "'") || (*it == "\"" && *(it + 2) == "\""))
        {
            it = tokens.erase(it);
            it = tokens.erase(it + 1);
        }
        else if (*it == "long")
        {
            if (*(it + 1) == "long")
            {
                if (match(data_types, it + 2))
                {
                    *it = *it + " " + (*(it + 1)) + " " + (*(it + 2));
                    data_types.push_back(*it);//Update database
                    it = tokens.erase(it + 1);
                    it = tokens.erase(it);
                }
                else
                {
                    *it = *it + " " + (*(it + 1));
                    data_types.push_back(*it);
                    it = tokens.erase(it + 1);
                }
            }
            else
            {
                if (match(data_types, it + 1))
                {
                    *it = *it + " " + (*(it + 1));
                    data_types.push_back(*it);
                    it = tokens.erase(it + 1);
                }
                else
                {
                    data_types.push_back(*it);
                    it++;
                }
            }
        }
        else if (match(data_types, it) && *(it + 1) == "*") //For pointers
        {
            *it += *(it + 1);
            data_types.push_back(*it);
            it = tokens.erase(it + 1);
        }
        else if (match(data_types, it) && *(it + 1) == "&") //For lvalue referenes
        {
            *it += *(it + 1);
            data_types.push_back(*it);
            it = tokens.erase(it + 1);
        }
        else if (match(data_types, it) && *(it + 1) == "&&") //For rvalue references
        {
            *it += *(it + 1);
            data_types.push_back(*it);
            it = tokens.erase(it + 1);
        }

        else
            it++;
    }
    //Formatting for containers cause of their unusual syntax :p
    it = tokens.begin();
    while (it != tokens.end())
    {
        if (match(containers, it) && *(it + 1) == "<" && match(data_types, (it + 2)) && *(it + 3) == ">")
        {
            if (*(it + 4) == "&" || *(it + 4) == "&&" || *(it + 4) == "*")
            {
                //vector<string>& etc...
                //Combining <, string, > and & into one to make it a 'datatype container (dtype_containers)'
                *(it + 1) += *(it + 2) + *(it + 3) + *(it + 4);
                //Add to data_types
                dtype_containers.push_back(*(it + 1));
                //Remove unnecessary entries
                it = tokens.erase(it + 2);
                it = tokens.erase(it);
                it = tokens.erase(it);
            }
            else //For non lvalue refr, rvalue refr, pointer typess
            {
                *(it + 1) += *(it + 2) + *(it + 3);
                dtype_containers.push_back(*(it + 1));
                it = tokens.erase(it + 2);
                it = tokens.erase(it);
            }
        }
        else
            it++;
    }

    return;
}
void parse()
{
    /*THE PLAY MAKER: THIS FUNCTION COMMMANDS!*/
    search_class();
    search_inhclass();

    //QMessageBox msg;
    //msg.setText("Parse exited successfully");
    //msg.exec();
    return;
}
void search_inhclass()
{
    vector<string>::iterator it = tokens.begin(); //Iterator to tokens vector

                                                  //Temporary places to hold members
    string name;
    vector<Variable*> pvt_var;
    vector<Function*> pvt_fun;
    vector<Variable*> prot_var;
    vector<Function*> prot_fun;
    vector<Variable*> pub_var;
    vector<Function*> pub_fun;
    vector<Function*> f_fun;
    vector<string> f_cls;
    vector<Function*> v_fun;
    //Flags
    bool found = false;
    string access;
    vector<string> modes = { "private", "public", "protected" };
    //Go through the tokens
    while (it != tokens.end())
    {
        if (*it == "class" && *(it + 2) == ":" && match(modes, it + 3))  //class Der : public Base
        {
            string n_bc = *(it + 4);
            name = *(it + 1);
            data_types.push_back(name);

            advance(it, 4); //At name of base class

            while (*it != "};")
            {
                access_change(it, &access);
                if (access == "private")
                {
                    if (search_var(it, pvt_var));
                    else if (search_arr(it, pvt_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, pvt_fun, name));
                    else if (search_container(it, pvt_var));
                    else
                        search_fun(it, pvt_fun);

                }
                else if (access == "public")
                {
                    if (search_var(it, pub_var));
                    else if (search_arr(it, pub_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, pub_fun, name));
                    else if (search_container(it, pub_var));
                    else
                        search_fun(it, pub_fun);
                }
                else if (access == "protected")
                {
                    if (search_var(it, prot_var));
                    else if (search_arr(it, prot_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, prot_fun, name));
                    else if (search_container(it, prot_var));
                    else
                        search_fun(it, prot_fun);
                }
                it++;
            }
            //One inherited class detected completely. Add to database
            Class* p_cls = new Class(name, pvt_var, pvt_fun, prot_var, prot_fun, pub_var, pub_fun, f_fun, f_cls, v_fun);
            p_cls->base_class = n_bc;
            p_cls->derived = true;

            classes.push_back(*p_cls);
            p_cls = &classes.back();
            //Link with the base class
            vector<Class>::iterator itr;
            for (itr = classes.begin(); itr != classes.end(); itr++)
            {
                if (itr->name == n_bc) //Found Base class
                {
                    found = true;
                    itr->inherited = true;
                    (itr->childs).push_back(p_cls); //Linkage done, hopefully :-/
                    pvt_var.clear();
                    pvt_fun.clear();
                    prot_var.clear();
                    prot_fun.clear();
                    pub_var.clear();
                    pub_fun.clear();
                    f_fun.clear();
                    f_cls.clear();
                    v_fun.clear();

                    break;
                }
            }

            it++;
        }
        else if (*it == "class" && *(it + 2) == ":" && !(match(modes, it + 3))) //class Der : Base
        {
            string n_bc = *(it + 3);
            name = *(it + 1);
            data_types.push_back(name);
            advance(it, 3);

            while (*it != "};")
            {
                access_change(it, &access);
                if (access == "private")
                {
                    if (search_var(it, pvt_var));
                    else if (search_arr(it, pvt_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else
                        search_fun(it, pvt_fun);

                }
                else if (access == "public")
                {
                    if (search_var(it, pub_var));
                    else if (search_arr(it, pub_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else
                        search_fun(it, pub_fun);
                }
                else if (access == "protected")
                {
                    if (search_var(it, prot_var));
                    else if (search_arr(it, prot_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else
                        search_fun(it, prot_fun);
                }
                it++;
            }
            //One inherited class detected completely. Add to classes database
            Class cls(name, pvt_var, pvt_fun, prot_var, prot_fun, pub_var, pub_fun, f_fun, f_cls, v_fun);
            cls.base_class = n_bc;
            cls.derived = true;
            classes.push_back(cls);

            //Link with the base class
            vector<Class>::iterator itr;
            for (itr = classes.begin(); itr != classes.end(); itr++)
            {
                if (itr->name == n_bc) //Found Base class
                {
                    found = true;
                    itr->inherited = true;
                    (itr->childs).push_back(&classes.back()); //Linkage done
                    pvt_var.clear();
                    pvt_fun.clear();
                    prot_var.clear();
                    prot_fun.clear();
                    pub_var.clear();
                    pub_fun.clear();
                    f_fun.clear();
                    f_cls.clear();
                    v_fun.clear();
                    break;
                }
            }

            it++;
        }
        else
        {
            it++;
        }
    }

    return;
}
void search_class()
{
    //Declaring an iterator for the tokens vector
    vector<string>::iterator it = tokens.begin();
    //Temporary places to hold members
    string name;
    vector<Variable*> pvt_var;
    vector<Function*> pvt_fun;
    vector<Variable*> prot_var;
    vector<Function*> prot_fun;
    vector<Variable*> pub_var;
    vector<Function*> pub_fun;
    vector<Function*> f_fun;
    vector<string> f_cls;
    vector<Function*> v_fun;
    //Flags
    string access;

    //Go through the tokens
    while (it != tokens.end())
    {
        if (*it == "class" && *(it + 2) == "{") //A class definition is starting
        {
            name = *(it + 1);
            //Add it to the data_types database
            data_types.push_back(name);
            //check for inheritence here as it will change things a bit
            //Access specifiers check
            while (*it != "};")
            {
                access_change(it, &access);
                if (access == "private")
                {
                    if (search_var(it, pvt_var));
                    else if (search_arr(it, pvt_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, pvt_fun, name));
                    else if (search_container(it, pvt_var));
                    else
                        search_fun(it, pvt_fun);

                }
                else if (access == "public")
                {
                    if (search_var(it, pub_var));
                    else if (search_arr(it, pub_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, pub_fun, name));
                    else if (search_container(it, pub_var));
                    else
                        search_fun(it, pub_fun);
                }
                else if (access == "protected")
                {
                    if (search_var(it, prot_var));
                    else if (search_arr(it, prot_var));
                    else if (search_frnd(it, f_cls, f_fun));
                    else if (search_vfun(it, v_fun));
                    else if (search_const(it, prot_fun, name));
                    else if (search_container(it, prot_var));
                    else
                        search_fun(it, prot_fun);
                }
                it++;
            }
            //One class detected completely. Add to classes database
            classes.push_back(Class(name, pvt_var, pvt_fun, prot_var, prot_fun, pub_var, pub_fun, f_fun, f_cls, v_fun));
            //Clear the containers
            pvt_var.clear();
            pvt_fun.clear();
            prot_var.clear();
            prot_fun.clear();
            pub_var.clear();
            pub_fun.clear();
            f_fun.clear();
            f_cls.clear();
            v_fun.clear();
        }
        else if (*it == "class" && *(it + 2) == ";") //A Forward Decleration
        {
            data_types.push_back(*(it + 1)); //Update the database for data types
        }

        it++;
    }

    return;

}

void search_param(vector<string>::iterator& pos, const vector<string>& b_points, vector<Variable*>& var)
{
    bool flag = false;
    /*function to search for variables between the specified iterator and words*/
    while(pos != tokens.end() && !match(b_points, pos))
    {
        /*TWO DIFFERENT CASES:
        1 - PARAMETERS ARE NAMED
        2 - PARAMETERS ARE UN-NAMED
        */
        //Search for data members (named)
        if (match(containers, pos) && match(dtype_containers, pos + 1) && (*(pos + 3) == "," || *(pos + 3) == ")"))
        {
            var.push_back(new Container(*(pos + 2), (*(pos)+*(pos + 1))));
        }
        else if (match(data_types, pos) && (*(pos + 2) == "," || *(pos+2) == ")"))
        {
            var.push_back(new Variable(*(pos + 1), *pos));
        }
        else if (match(data_types, pos) && *(pos + 2) == "[")
        {
            var.push_back(new Array(*(pos + 1), *pos, "param"));
        }
        //Search for data members (un-named)
        else if (match(containers, pos) && match(dtype_containers, pos + 1) && (*(pos + 2) == "," || *(pos + 2) == ")"))
        {
            var.push_back(new Container("*NOT NAMED*", (*(pos)+*(pos + 1))));
        }
        else if (match(data_types, pos) && (*(pos + 1) == "," || *(pos + 1) == ")"))
        {
            var.push_back(new Variable("*NOT NAMED*", *pos));
        }
        else if (match(data_types, pos) && *(pos + 1) == "[")
        {
            var.push_back(new Array("*NOT NAMED*", *pos, "param"));
        }
        pos++;
    }
    return;
}
bool search_var(vector<string>::iterator& pos, vector<Variable*>& var)
{
    string name;
    string type;

    //Search for data members
    if (match(data_types, pos) && *(pos + 2) == "=" && *(pos + 4) == ";") //int &a = 5;
    {
        //Add to variables
        var.push_back(new Variable(*(pos + 1), *pos));
        //Advance the iterator. No need to waste energy
        advance(pos, 4);
        return true;
    }
    else if (match(data_types, pos) && *(pos + 2) == ";") //int a;
    {
        //Add to variables
        var.push_back(new Variable(*(pos + 1), *pos));
        //Advance the iterator. No need to waste energy
        advance(pos, 2);
        return true;
    }
    else if (match(data_types, pos) && *(pos + 2) == "," && *(pos-1) != "(") //int a, b;
    {
        vector<string>::iterator end = pos + 1;
        while (*end != ";")
        {
            if (*end != ",")
            {
                var.push_back(new Variable(*end, *pos));
                end++;
            }
            else
                end++;
        }
        pos = end; //Move the iterator forward to the semicolon
        return true;
    }
    //No variable found
    return false;
}
bool search_arr(vector<string>::iterator& pos, vector<Variable*>& var)
{
    string name;
    string type;
    int elem = 0;

    //Search for array members
    if ((match(data_types, pos) && *(pos + 2) == "[" && *(pos + 4) == "]" && *(pos + 5) == "=") || (match(data_types, pos) && *(pos + 2) == "[" && *(pos + 4) == "]" && *(pos + 5) == ";")) //int a[x] =  || int a[x];
    {
        var.push_back(new Array(*(pos + 1), *pos, *(pos+3)));
        return true;
    }
    //No array found
    return false;
}
bool search_fun(vector<string>::iterator& pos, vector<Function*>& fun)
{
    //Regular expression:
    regex expr("\\((.*)\\)");

    string substr;
    string name;
    string r_type;
    vector<Variable*> param;

    //Search for member functions
    if (match(data_types, pos))
    {
        //First, identify a semicolon
        vector<string>::iterator start = pos+2;
        vector<string>::iterator end = pos;

        while (*end != ";")
        {
            end++;
        }
        copy(start, end, substr);
        if (regex_match(substr, expr)) //a function
        {
            r_type = *pos;
            name = *(pos + 1);
            vector<string> b_point = { ")" };
            vector<string>::iterator it1 = pos + 3;
            search_param(it1, b_point, param);

            if (param.size() == 0)
            {
                fun.push_back(new Function(name, r_type));
                pos = end;
                return true;
            }
            else
            {
                fun.push_back(new Function(name, r_type, param));
                pos = end;
                return true;
            }

        }
    }
    //Not found
    return false;
}
bool search_frnd(vector<string>::iterator& pos, vector<string>& f_cls, vector<Function*>& f_fun)
{
    if (*pos == "friend")
    {
        vector<string>::iterator it = pos + 1;
        if (search_fun(it, f_fun)) { pos = it; return true; } //either a friend function
        else if (*(pos + 1) == "class") //or a friend class
        {
            f_cls.push_back(*(pos + 2));
            pos = (pos + 3);
            return true;
        }
    }

    return false;
}
bool search_vfun(vector<string>::iterator& pos, vector<Function*>& v_fun)
{
    if (*pos == "virtual")
    {
        vector<string>::iterator it = pos + 1;
        if (search_fun(it, v_fun)) { pos = it; return true; } //a virtual function
    }

    return false;
}
bool search_const(vector<string>::iterator& pos, vector<Function*>& constr, string c_name)
{
    regex expr("\\((.*)\\)");
    string substr;
    string name = c_name;
    vector<Variable*> param;

    if (*pos == c_name && *(pos + 1) == "(")
    {
        //First, identify a semicolon
        vector<string>::iterator start = pos + 1;
        vector<string>::iterator end = pos;

        while (*end != ";")
        {
            end++;
        }
        copy(start, end, substr);
        if (regex_match(substr, expr)) //a function
        {
            vector<string> b_point = { ")" };
            vector<string>::iterator it1 = pos + 2;
            search_param(it1, b_point, param);

            if (param.size() == 0)
            {
                constr.push_back(new Constructor(name));
                pos = end;
                return true;
            }
            else
            {
                constr.push_back(new Constructor(name, param));
                pos = end;
                return true;
            }
        }
    }

    return false;
}
bool search_container(vector<string>::iterator& pos, vector<Variable*>& cont)
{
    string name;
    string type;
    /*string d_type;
    string c_type;
    string pass_as;*/

    if (match(containers, pos))
    {
        name = *(pos + 2);
        type = *pos + *(pos + 1);

        cont.push_back(new Container(name, type));

        advance(pos, 2);

        return true;
    }

    return false;
}
bool letter(char c)
{
    /*FUNCTION  TO CHECK IF A CHARACTER IS AN ALPHABET OR NOT*/

    if ((static_cast<int>(c) >= 65 && static_cast<int>(c) <= 90) || (static_cast<int>(c) >= 97 && static_cast<int>(c) <= 122))
    {
        return true;
    }
    else
        return false;
}
bool digit(char c)
{
    /*FUNCTION  TO CHECK IF A CHARACTER IS A DIGIT OR NOT*/

    if (static_cast<int>(c) >= 48 && static_cast<int>(c) <= 57)
    {
        return true;
    }
    else
        return false;
}
bool underscore(char c)
{
    if (c == '_')
        return true;
    else
        return false;
}
bool match(const vector<string>& flags, const vector<string>::iterator& pos)
{
    for (auto it = flags.begin(); it != flags.end(); it++)
    {
        if (*pos == *it)
        {
            return  true;
        }
    }
    return false;
}
bool access_change(vector<string>::iterator& it, string *access)
{
    if (*it == "class" && (*(it + 3) == "private" || *(it + 3) == "public" || *(it + 3) == "protected"))
    {
        *access = *(it + 3);
        return true;
    }
    else if (*it == "class" && *(it + 3) != "private" && *(it + 3) != "public" && *(it + 3) != "protected")
    {
        *access = "private";
        return true;
    }
    else if (*it == "private" || *it == "public" || *it == "protected")
    {
        *access = *it;
        return true;
    }
    return false;
}

void copy(int f, int t)
{
    string str;

    for (; f <= t; f++)
    {
        str.push_back(buffer[f]);
    }
    tokens.push_back(str);

    return;
}
void copy(vector<string>::iterator& start, vector<string>::iterator& end, string& substr)
{
    while (start != end)
    {
        substr += *start;
        start++;
    }
    return;
}
