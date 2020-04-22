#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class Button : public QPushButton
{
private:
    static int count;
public:
    Button(const QString, QWidget *parent = nullptr);
};

#endif // BUTTON_H
