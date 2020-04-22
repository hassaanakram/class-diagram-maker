#include "../Headers/win_main.h"
#include "../Headers/button.h"
#include "../Headers/globals.h"
#include <QFileDialog>
#include <QObject>
#include <QMessageBox>

using std::string;
using std::ifstream;

Win_main::Win_main(QWidget *parent) : QWidget(parent)
{
    //Set windows size
    this->setFixedSize(230,330);
    //Create buttons
    b_open = new Button("Open File", this);
    b_write = new Button("Write Code", this);
    b_help = new  Button("Help", this);
    b_exit = new Button("Exit", this);

    QObject::connect(b_open, SIGNAL(clicked(bool)), this, SLOT(slotOpenFile(bool)));
}
//Slots
void Win_main::slotOpenFile(bool clicked)
{
    QString file = QFileDialog::getOpenFileName(this, "Open File", "C:/Users", "Documents(*.txt *.cpp *.h)");
    //Convert the file path to STL String
    string file_path = file.toUtf8().constData();
    ifstream input;

    //Opening file
            input.open(file_path);
            //Checking for the validity of input file path
            if (!input)
            {
               //Error dialogue
            }
            else
            {
                //File open successful, now extracting characters from it into a string
                extract_chars(input);
                //Now close the file
                input.close();
                //Success Message
                QMessageBox msg;
                msg.setText("File Read successfuly, Click OK to Proceed");
                msg.exec();
                commence(this);
                msg.setText("Processed");
                msg.exec();
            }
}

