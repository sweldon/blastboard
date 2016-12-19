#include <QApplication>
#include "window.h"
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    Window window;

    QProgressBar *bar = new QProgressBar(&window);

    bar->setRange(0,100);
    bar->setValue(0);
    bar->setGeometry(10,10,180,30);

    QSlider *slider = new QSlider(&window);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setGeometry(10,40, 180,30);



    window.show();



    QObject::connect(slider, SIGNAL(valueChanged(int)), bar, SLOT(setValue(int)));

    return app.exec();
}


