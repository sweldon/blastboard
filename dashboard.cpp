#include "dashboard.h"
#include "ui_dashboard.h"
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include "login.h"
#include <QtSql>
#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

Dashboard::Dashboard(QWidget *parent, QString username) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{


    QString user = username;

    ui->setupUi(this);
    this->setFixedSize(QSize(1250, 750));

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setStyleSheet("background: transparent");
    ui->user_label->setText(user);

    QSqlQuery update_blaster;
    update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+user+"'");

//    avatar = new QGraphicsEllipseItem(10,10,80,80);


    QPixmap m(":/assets/avatar_sample.png");

    QPen pen("#6996AD");
    pen.setWidth(-1);

    int avatarW = 80;
    int avatarH = 80;

    avatar = scene->addEllipse(0,0,avatarW,avatarH, pen, QBrush(m.scaled(avatarW,avatarH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));


    if(ui->progressBar->value() == 0) {
        ui->progressBar->setFormat("No blasters");
    }


    QSignalMapper* m_sigmapper = new QSignalMapper(this);

    // #2
    connect(ui->comboBox, SIGNAL(activated(int)), m_sigmapper, SLOT(map()));
    m_sigmapper->setMapping(ui->comboBox, user);

    connect(m_sigmapper, SIGNAL(mapped(QString)), this, SLOT(blast_selected(const QString&)));

//    QObject::connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(blast_selected(username)));


}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::blast_selected(QString username){


    QSqlQuery update_blaster;
    QSqlQuery status_blaster;
    // the status of the progressbar has to be saved in the database

    int selection =  ui->comboBox->currentIndex();
    QString status =  ui->comboBox->currentText();

    pgbar = ui->progressBar;
    int currentStatus = pgbar->value();

    if(selection == 1){

        if(status_blaster.exec("select * from users where blaster = FALSE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){

                    if(update_blaster.exec("UPDATE users SET blaster = TRUE WHERE username='"+username+"'")){

                        currentStatus += 20;
                        pgbar->setValue(currentStatus);
                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);

                        if(currentStatus == 100){
                            pgbar->setStyleSheet("QProgressBar{ border: 2px solid grey;border-radius: 5px;text-align: center}QProgressBar::chunk {background-color: green;width: 10px;margin: 1px;}");
                            pgbar->setFormat("");
                        }
                        else{
                            pgbar->setFormat("");
                        }

                    }else{
                        qDebug() << update_blaster.lastError().text();
                    }

                }else{
                    pgbar->setFormat("");
                    int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);
                    ui->listWidget->item(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]))->setText(username);
                    ui->statusList->item(playerIndex)->setText(status);
                    if(currentStatus==0){
                        currentStatus += 20;
                        pgbar->setValue(currentStatus);
                    }

                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }

    }
    else if(selection == 0){


        if(status_blaster.exec("select * from users where blaster = TRUE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){

                    if(update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+username+"'")){

                        if(currentStatus > 0){
                            currentStatus -= 20;
                            pgbar->setValue(currentStatus);
                        }

                        int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);

                        ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]));
                        ui->statusList->takeItem(playerIndex);

                        if(currentStatus == 0){
                            pgbar->setFormat("No blasters");
                        }
                        else{
                            pgbar->setFormat("");
                        }

                    }else{
                        qDebug() << update_blaster.lastError().text();
                    }

                }else{

                    qDebug() << "Blaster is already unready";
                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }



    }
    else{


        if(status_blaster.exec("select * from users where blaster = TRUE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){
//                        update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+username+"'");

                        if(currentStatus > 0){
                            currentStatus -= 20;
                            pgbar->setValue(currentStatus);
                        }
                        int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);
                        ui->listWidget->item(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]))->setText(username);
                        ui->statusList->item(playerIndex)->setText(status);

                        if(currentStatus == 0){
                            pgbar->setFormat("No blasters");
                        }
                        else{
                            pgbar->setFormat("");
                        }



                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }

    }

    if(currentStatus < 100){
        pgbar->setStyleSheet("QProgressBar{ border: 2px solid grey;border-radius: 5px;text-align: center}QProgressBar::chunk {background-color: red;width: 10px;margin: 1px;}");
    }


}
