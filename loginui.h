#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

private:
    Ui::LoginUi *ui;
};

#endif // LOGINUI_H
