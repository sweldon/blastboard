#include "login.h"
#include <QPushButton>
#include <QApplication>
#include <QProgressBar>
#include <QSlider>
#include <QLineEdit>
#include <QtSql>
#include <QSqlDatabase>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>

Login::Login(QWidget *parent) : QWidget(parent){

    sqldb = new QSqlDatabase;
    sqldb->addDatabase("QMYSQL");
    sqldb->setDatabaseName("blastboard");
    sqldb->setHostName("localhost");
    sqldb->setUserName("root");
    sqldb->setPassword("password");
    bool ok = sqldb->isOpen();

    setFixedSize(350, 400);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/assets/blast_3.png")));

    setPalette(palette);

    user_field = new QLineEdit(this);
    user_field -> setGeometry(50, 250, 245, 30);
    user_field->setStyleSheet("background: none; background-color: #ffffff;font-size:18pt; border-radius:2px; font-family:'Arial'; ");
    user_field->setPlaceholderText("Username");

    pass_field = new QLineEdit(this);
    pass_field -> setGeometry(50, 295, 245, 30);
    pass_field->setPlaceholderText("Password");
    pass_field->setStyleSheet("background: none; background-color: #ffffff; font-size:18pt; border-radius:2px; font-family:'Arial';");
    pass_field->setEchoMode(QLineEdit::Password);

    submit_login = new QPushButton("Blast",this);
    submit_login->setGeometry(110, 345, 125, 35);
    submit_login->setStyleSheet("QPushButton{background: none; background-color:#98B2BD; height: 5px; color: #ffffff; font-size:16pt; font-family:'Arial'; border-radius:2px;} QPushButton:hover{background-color:#798e97;}");

    QObject::connect(submit_login, SIGNAL(clicked(bool)), this, SLOT(on_login_clicked()));

    if(!ok){
        qDebug() << "Failed to open db connection!";
        return;
    }

}

void Login::on_login_clicked(){


    QString username, password;
    username = user_field->text();
    password = pass_field->text();

    QSqlQuery login_query;

    if(login_query.exec("select * from users where username = '"+username+"' and password = '"+password+"'")){

            int executions;
            while(login_query.next()){
                executions++;
            }

            if(executions == 1){
                submit_login->setText("Login success.");
            }
            else if(executions > 1){
                submit_login->setText("Duplicate username and password.");
            }
            else if(executions < 1){
                submit_login->setText("You've entered the wrong shit.");
            }

    }


}

