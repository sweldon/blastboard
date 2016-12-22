#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QTableWidget>


namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

private:
    Ui::Dashboard *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *avatar;
    QProgressBar *pgbar;
    QTableWidget *vTable;

private slots:
    void blast_selected();


};

#endif // DASHBOARD_H
