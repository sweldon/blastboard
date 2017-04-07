#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QMouseEvent>

class toolbar : public QWidget
{
    Q_OBJECT
public:
    explicit toolbar(QWidget *parent = 0);
    QWidget* mainWindow;

signals:

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;



public slots:
};

#endif // TOOLBAR_H
