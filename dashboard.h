#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QTableWidget>
#include <QLabel>
#include <QSqlDatabase>


namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0, QString username = NULL);
    ~Dashboard();

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
    Ui::Dashboard *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *avatar;
    QProgressBar *pgbar;
    QTableWidget *vTable;
    QLabel *connection_error;

private slots:
    void blast_selected(QString username);


};

#endif // DASHBOARD_H
