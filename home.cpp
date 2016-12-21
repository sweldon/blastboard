#include "home.h"
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

Home::Home(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1250, 750);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor("#3f3f3f")));
    setPalette(palette);


}
