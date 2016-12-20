#include <QApplication>
#include "login.h"
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <QtSql>

// /Users/weldos01/build-blastboard-Desktop_Qt_5_7_1_clang_64bit-Release

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

      Login login_window;

      login_window.show();


    return app.exec();
}


