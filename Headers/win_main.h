#ifndef WIN_MAIN_H
#define WIN_MAIN_H

#include <QWidget>
#include <QPushButton>

class Win_main : public QWidget
{
    Q_OBJECT
public:
   explicit Win_main(QWidget *parent = nullptr);
private:
    QPushButton *b_open;
    QPushButton *b_write;
    QPushButton *b_help;
    QPushButton *b_exit;

signals:
private slots:
    void slotOpenFile(bool);
    //void slotWriteCode(bool);
    //void slotHelp(bool);
    //void slotExit(bool);
};

#endif // WIN_MAIN_H
