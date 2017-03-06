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
#include <QMessageBox>
#include <bot.h>

Login::Login(QWidget *parent) : QWidget(parent){

    if(!connOpen()){

        connection_error = new QLabel("Error: Can't connect to Blastboard servers", this);
        connection_error->setGeometry(0, 0, 350, 25);
        connection_error->setStyleSheet("background-color:#cc0000; text-align:center;");
        connection_error->setAlignment(Qt::AlignCenter);


    }

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

    this->setWindowTitle("Blastboard - Login");

}

void Login::on_login_clicked(){


    QString username, password;
    username = user_field->text();
    password = pass_field->text();

    QSqlQuery login_query;


    if(login_query.exec("select * from users where username = '"+username+"' and password = '"+password+"'")){

            int executions = 0;
            while(login_query.next()){
                executions++;
            }

            if(executions == 1){
                this->hide();
//                Dashboard *dashboard = new Dashboard(NULL, username);
//                dashboard->show();
                Bot *b = new Bot();
            }
            if(executions > 1){
                // this case makes no sense. get rid of it later.
                submit_login->setText("Duplicate...");
            }
            if(executions < 1){
                submit_login->setText("You've entered the wrong shit.");
            }

    }


}

