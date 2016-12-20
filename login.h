#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QWidget>
#include <QSqlDatabase>

class QPushButton;
class QLineEdit;

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);

signals:


private slots:
    void on_login_clicked();


private:
    QSqlDatabase *sqldb;
    QLineEdit *user_field;
    QLineEdit *pass_field;
    QPushButton *submit_login;
    bool *ok;

};

#endif // LOGIN_H
