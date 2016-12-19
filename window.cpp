#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>

Window::Window(QWidget *parent) : QWidget(parent){

    setFixedSize(1350, 750);
    setStyleSheet("background-color: #262626;");
    m_button = new QPushButton("Close", this);
    m_button -> setGeometry(10, 80, 80, 30);

    m_button->setCheckable(true);

    m_counter = 0;

    connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));

    connect(this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));

    infoButton = new QPushButton("About", this);
    infoButton -> setGeometry(10, 120, 80, 30);
    infoButton -> setCheckable(true);

    infoButton->setStyleSheet("background-color: #ffffff");
    m_button->setStyleSheet("background-color: #ffffff");

    connect(infoButton, SIGNAL(clicked(bool)), this, SLOT(showAbout(bool)));


}

void Window::slotButtonClicked(bool checked){
    if(checked){
        m_button->setText("Checked");
    }else{
        m_button->setText("Hello World");
    }
    m_counter++;
    if(m_counter == 5){
        emit counterReached();
    }
}

void Window::showAbout(bool checked){
    if(checked){

        QMessageBox *msgBox = new QMessageBox(0);
        msgBox->setWindowTitle("title");
        msgBox->setText("Question");
        msgBox->setStandardButtons(QMessageBox::Yes);
        msgBox->addButton(QMessageBox::No);
        msgBox->setDefaultButton(QMessageBox::No);
        if(msgBox->exec() == QMessageBox::Yes){
          emit counterReached();
        }else {
          // do something else
        }

    }
}
