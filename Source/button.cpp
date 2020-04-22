#include "../Headers/button.h"

//To count the number of buttons created
int Button::count = 0;
//Constructor
Button::Button(const QString title, QWidget *parent) : QPushButton(title, parent)
{
    this->setGeometry(10,(count*70)+10,210,70);
    count++;
}
