/*CS212: END SEMESTER PROJECT (UML CONVERSION)*/

/*THINGS THAT I AM OVERLOOKIN:
    1 - CLASS TEMPELATES
    2 - FUNCTION TEMPELATES
    3 - OPERATOR OVERLOADS
    4 - STRUCTS*/
//Qt
#include <QApplication>
#include <QMessageBox>
#include "../Headers/win_main.h"
/*GLOBALS*/
#include "../Headers/globals.h"

/*-----------------------------------main-------------------------------------*/
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Win_main main_window;
    main_window.show();

    return app.exec();
}
