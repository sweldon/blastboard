#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

signals:
    void counterReached();

private slots:
    void slotButtonClicked(bool checked);
    void showAbout(bool checked);

private:
    QPushButton *m_button;
    QPushButton *infoButton;
    int m_counter;



};

#endif // WINDOW_H
