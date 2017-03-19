#ifndef CHATBOXHANDLER_H
#define CHATBOXHANDLER_H

#include <QTextEdit>
#include <dashboard.h>

class chatBoxHandler : public QTextEdit
{
    Q_OBJECT
public:
    explicit chatBoxHandler(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *e);

private:


public slots:

signals:

};

#endif // CHATBOXHANDLER_H
