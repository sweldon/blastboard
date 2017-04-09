#include "loginui.h"
#include "ui_loginui.h"
#include "dashboard.h"
#include <QDebug>
LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    if(!connOpen()){

        connection_error = new QLabel("Error: Can't connect to Blastboard servers", this);
        connection_error->setGeometry(0, 30, 350, 25);
        connection_error->setStyleSheet("background-color:#cc0000; text-align:center;");
        connection_error->setAlignment(Qt::AlignCenter);

        qDebug() << "nope";

    }

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/assets/blast_3.png")));

    setPalette(palette);

    ui->user_field->setPlaceholderText("Username");
    ui->pass_field->setPlaceholderText("Password");
    ui->pass_field->setEchoMode(QLineEdit::Password);

    QObject::connect(ui->submit_login, SIGNAL(clicked(bool)), this, SLOT(on_login_clicked()));
    QObject::connect(ui->pass_field, SIGNAL(returnPressed()), this, SLOT(on_login_clicked()));

    connect(ui->close_button, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(ui->min_button, SIGNAL(clicked(bool)), this, SLOT(minimizeWindow()));

}

LoginUi::~LoginUi()
{
    delete ui;
}

void LoginUi::on_login_clicked(){


    QString username, password;
    username = ui->user_field->text();
    password = ui->pass_field->text();

    QSqlQuery login_query;


    if(login_query.exec("select * from users where username = '"+username+"' and password = '"+password+"'")){

            int executions = 0;
            while(login_query.next()){
                executions++;
            }

            if(executions == 1){
                this->hide();
                Dashboard *dashboard = new Dashboard(NULL, username, password);
                dashboard->show();
            }
            if(executions > 1){
                // this case makes no sense. get rid of it later.
                ui->submit_login->setText("Duplicate...");
            }
            if(executions < 1){
                ui->submit_login->setText("You've entered the wrong shit.");
            }

    }


}

void LoginUi::closeWindow(){
    QApplication::quit();
}

void LoginUi::minimizeWindow() {
    this->setWindowState(Qt::WindowMinimized);
}
