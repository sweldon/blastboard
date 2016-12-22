#include <QApplication>
#include "login.h"
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <QtSql>
#include <dashboard.h>

// temporary for main screen development
#include <dashboard.h>

// /Users/weldos01/build-blastboard-Desktop_Qt_5_7_1_clang_64bit-Release

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

         Login login_window;

         login_window.show();


        // temporary for main screen development
//        Dashboard home;

//        home.show();


    return app.exec();
}


