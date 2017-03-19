#include "chatboxhandler.h"
//#include "dashboard.h"
#include <QDebug>

#include <QKeyEvent>

chatBoxHandler::chatBoxHandler(QWidget *parent) :
    QTextEdit(parent)
{
}

void chatBoxHandler::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Return){
//        d->sendBlastMessage();
        qDebug() << "pressed enter! send a message";
    }else{
        QTextEdit::keyPressEvent( event );
    }


}
