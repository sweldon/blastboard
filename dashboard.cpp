#include "dashboard.h"
#include "ui_dashboard.h"
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <QDebug>

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setStyleSheet("background: transparent");


//    avatar = new QGraphicsEllipseItem(10,10,80,80);


    QPixmap m(":/assets/avatar_sample.png");


    QPen pen("#6996AD");
    pen.setWidth(-1);

    int avatarW = 80;
    int avatarH = 80;

    avatar = scene->addEllipse(0,0,avatarW,avatarH, pen, QBrush(m.scaled(avatarW,avatarH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));



    QObject::connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(blast_selected()));


}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::blast_selected(){

    // the status of the progressbar has to be saved in the database

    int selection =  ui->comboBox->currentIndex();
    pgbar = ui->progressBar;
    int currentStatus = pgbar->value();

    if(selection == 2){

        if(currentStatus == 5){
            pgbar->setValue(25);
        }
        else if(currentStatus == 100){
            pgbar->setStyleSheet("background-color:green;");
        }
        else{
            currentStatus += 25;
        }
    }
    else{
        if(currentStatus == 25){
            pgbar->setValue(5);
        }
        else{
            currentStatus -=25;
        }
    }


}
