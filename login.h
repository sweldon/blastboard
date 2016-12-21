#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QWidget>
#include <QSqlDatabase>
#include "home.h"
#include <QLabel>


class QPushButton;
class QLineEdit;

class Login : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase sqldb;

    void connClose(){

        sqldb.close();
        sqldb.removeDatabase(QSqlDatabase::defaultConnection);

    }

    bool connOpen(){

        sqldb = QSqlDatabase::addDatabase("QPSQL");
        sqldb.setHostName("localhost");
        sqldb.setDatabaseName("blastboard");
        sqldb.setUserName("postgres");
        sqldb.setPassword("password");
        sqldb.setPort(5432);

        bool ok = sqldb.open();

        return ok;
    }

public:
    explicit Login(QWidget *parent = 0);

signals:


private slots:
    void on_login_clicked();


private:
    QLineEdit *user_field;
    QLineEdit *pass_field;
    QDialogButtonBox *submit_login;
    bool *ok;
    QLabel *connection_error;


};

#endif // LOGIN_H
