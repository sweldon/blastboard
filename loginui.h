#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QSqlDatabase>
#include <QLabel>
#include <QtSql>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

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

private:
    Ui::LoginUi *ui;
    QLabel *connection_error;
    bool *ok;


private slots:
    void on_login_clicked();
    void closeWindow();
    void minimizeWindow();



};

#endif // LOGINUI_H
