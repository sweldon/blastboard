#include <QApplication>

#include "loginui.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    LoginUi w;
    w.show();

    return a.exec();
}


