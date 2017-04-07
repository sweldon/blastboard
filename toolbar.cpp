#include "toolbar.h"
#include "dashboard.h"
toolbar::toolbar(QWidget *parent) : QWidget(parent)
{
 mainWindow = QWidget::window ();
 this->raise();
}
void toolbar::mousePressEvent(QMouseEvent *event) {

m_nMouseClick_X_Coordinate = event->x();
m_nMouseClick_Y_Coordinate = event->y();
}

void toolbar::mouseMoveEvent(QMouseEvent *event) {
    this->mainWindow->move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);

}
