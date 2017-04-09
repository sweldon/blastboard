#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/assets/blast_3.png")));

    setPalette(palette);

    ui->user_field->setPlaceholderText("Username");
    ui->pass_field->setPlaceholderText("Password");
}

LoginUi::~LoginUi()
{
    delete ui;
}
