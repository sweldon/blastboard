#include "dashboard.h"
#include "ui_dashboard.h"
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QtSql>
#include <gloox/messagehandler.h>

Dashboard::Dashboard(QWidget *parent, QString un, QString pw) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{

    std::string username = un.toUtf8().constData();
    std::string password = pw.toUtf8().constData();


    ui->setupUi(this);
    this->setFixedSize(QSize(1250, 750));

    ui->chatDialog->setText("<p><i>-You have entered the blastboard chat</i></p>");

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setStyleSheet("background: transparent");
    ui->user_label->setText(un);
    jid = JID(username+"@earthworkx.com");
    client = new Client(jid, password);
    client->registerConnectionListener(this);
    client->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);
    client->rosterManager()->registerRosterListener(this);
    client->registerMessageHandler(this);
    client->setSasl(true);
    recvThread = new RecvThread(client);
    recvThread->start();
    client->connect(false);

    vcardManager = new VCardManager(client);

    QSqlQuery update_blaster;
    update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+un+"'");

    //avatar = new QGraphicsEllipseItem(10,10,80,80);


    QPixmap m(":/assets/avatar_sample.png");

    QPen pen("#6996AD");
    pen.setWidth(-1);

    int avatarW = 80;
    int avatarH = 80;

    avatar = scene->addEllipse(0,0,avatarW,avatarH, pen, QBrush(m.scaled(avatarW,avatarH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

    if(ui->progressBar->value() == 0) {
        ui->progressBar->setFormat("No blasters");
    }


    QSignalMapper* m_sigmapper = new QSignalMapper(this);

    connect(ui->comboBox, SIGNAL(activated(int)), m_sigmapper, SLOT(map()));
    m_sigmapper->setMapping(ui->comboBox, un);

    connect(m_sigmapper, SIGNAL(mapped(QString)), this, SLOT(blast_selected(const QString&)));
    connect(ui->sendMsgBtn, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
    // QObject::connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(blast_selected(username)));

    connect(ui->sendMsgBtn, SIGNAL(returnPressed()),this,SIGNAL(clicked()));


}

Dashboard::~Dashboard()
{
    recvThread->stop();
    delete ui;
}

void Dashboard::sendMessage(){
    QString msg = ui->messageDraft->toPlainText().trimmed();
    if(msg!=""){
        string ptmsg = msg.toUtf8().constData();
        Message msg_back(Message::Chat,gloox::JID("admin@earthworkx.com"), ptmsg);
        client->send( msg_back );
        QString username = QString::fromStdString(jid.username());
        ui->chatDialog->append("<b>"+username+"</b>: "+msg);
        ui->messageDraft->clear();
    }
    else{
        ui->messageDraft->clear();
    }

}

void Dashboard::blast_selected(QString username){


    QSqlQuery update_blaster;
    QSqlQuery status_blaster;
    // the status of the progressbar has to be saved in the database

    int selection =  ui->comboBox->currentIndex();
    QString status =  ui->comboBox->currentText();

    pgbar = ui->progressBar;
    int currentStatus = pgbar->value();

    if(selection == 1){

        if(status_blaster.exec("select * from users where blaster = FALSE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){

                    if(update_blaster.exec("UPDATE users SET blaster = TRUE WHERE username='"+username+"'")){

                        currentStatus += 20;
                        pgbar->setValue(currentStatus);
                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);

                        if(currentStatus == 100){
                            pgbar->setStyleSheet("QProgressBar{ border: 2px solid grey;border-radius: 5px;text-align: center}QProgressBar::chunk {background-color: green;width: 10px;margin: 1px;}");
                            pgbar->setFormat("");
                        }
                        else{
                            pgbar->setFormat("");
                        }

                    }else{
                        qDebug() << update_blaster.lastError().text();
                    }

                }else{
                    pgbar->setFormat("");
                    int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);
                    ui->listWidget->item(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]))->setText(username);
                    ui->statusList->item(playerIndex)->setText(status);
                    if(currentStatus==0){
                        currentStatus += 20;
                        pgbar->setValue(currentStatus);
                    }

                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }

    }
    else if(selection == 0){


        if(status_blaster.exec("select * from users where blaster = TRUE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){

                    if(update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+username+"'")){

                        if(currentStatus > 0){
                            currentStatus -= 20;
                            pgbar->setValue(currentStatus);
                        }

                        int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);

                        ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]));
                        ui->statusList->takeItem(playerIndex);

                        if(currentStatus == 0){
                            pgbar->setFormat("No blasters");
                        }
                        else{
                            pgbar->setFormat("");
                        }

                    }else{
                        qDebug() << update_blaster.lastError().text();
                    }

                }else{

                    qDebug() << "Blaster is already unready";
                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }



    }
    else{


        if(status_blaster.exec("select * from users where blaster = TRUE and username = '"+username+"'")){

                int executions = 0;
                while(status_blaster.next()){
                    executions++;
                }

                if(executions == 1){
//                        update_blaster.exec("UPDATE users SET blaster = FALSE WHERE username='"+username+"'");

                        if(currentStatus > 0){
                            currentStatus -= 20;
                            pgbar->setValue(currentStatus);
                        }
                        int playerIndex = ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]);
                        ui->listWidget->item(ui->listWidget->row(ui->listWidget->findItems(username, Qt::MatchContains)[0]))->setText(username);
                        ui->statusList->item(playerIndex)->setText(status);

                        if(currentStatus == 0){
                            pgbar->setFormat("No blasters");
                        }
                        else{
                            pgbar->setFormat("");
                        }



                }
        }else{
            qDebug() << update_blaster.lastError().text();
        }

    }

    if(currentStatus < 100){
        pgbar->setStyleSheet("QProgressBar{ border: 2px solid grey;border-radius: 5px;text-align: center}QProgressBar::chunk {background-color: red;width: 10px;margin: 1px;}");
    }


}

void Dashboard::onConnect()
{
//    ui->statusBar->showMessage("Logged in");
    qDebug() << "ConnListener::onConnect()" << endl;
    vcardManager->fetchVCard(jid.bare(), this);
}

void Dashboard::onDisconnect(ConnectionError e)
{
//    ui->statusBar->showMessage("Disconnected "+QString::number(e));
    qDebug() << "ConnListener::onDisconnect() " << e <<" "<<ConnNoSupportedAuth << endl;
}

void Dashboard::handleMessage( const Message& stanza, MessageSession* session = 0 ) {
    if(stanza.body() != ""){
        QString msg = QString::fromStdString(stanza.body());
        QString sender = QString::fromStdString(stanza.from().username());
        ui->chatDialog->append("<b>"+sender+"</b>: "+msg);
    }
}

void Dashboard::handleLog(LogLevel level, LogArea area, const string &message)
{
    qDebug()<< "log: level: "<<level<<", area: "<<area<<", "<<message.c_str();

}

void Dashboard::handleVCard(const JID &jid, const VCard *v)
{

    qDebug()<<"Received a vcard"<<endl;
    if( !v )
    {
        qDebug()<<"empty vcard!"<<endl;
        return;
    }

//    VCard* vcard = new VCard( *v );
//    string fn = vcard->formattedname();
//    qDebug()<<fn.c_str()<<endl;
//    VCard::Photo photo = vcard->photo();
//    ui->nameLabel->setText(QString(fn.c_str()));
//    string p = photo.binval;
//    for (int i=0; i<10; i++) cout<<(int) p[i]<<" "; cout<<endl;
//    QByteArray imageData(p.c_str(), p.size());
//    QImage image;
//    qDebug()<<image.loadFromData(imageData, "PNG");
//    qDebug()<<image.save("/home/dipal/a.png", "PNG");
//    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
//    ui->imageLabel->show();
}

void Dashboard::handleVCardResult(VCardHandler::VCardContext context, const JID &jid, StanzaError se)
{

}

void Dashboard::insertFriend(QString friendJid)
{
//    model->insertRow(model->rowCount());
//    QModelIndex index = model->index(model->rowCount()-1);
//    model->setData(index, friendJid);
}


void Dashboard::handleItemAdded(const JID &jid)
{
}

void Dashboard::handleItemSubscribed(const JID &jid)
{
}

void Dashboard::handleItemRemoved(const JID &jid)
{
}

void Dashboard::handleItemUpdated(const JID &jid)
{
}

void Dashboard::handleItemUnsubscribed(const JID &jid)
{
}

void Dashboard::handleRoster(const Roster &roster)
{
    Roster::const_iterator it = roster.begin();
    for( ; it != roster.end(); ++it )
    {
        insertFriend((*it).second->jidJID().full().c_str());
    }
}

void Dashboard::handleRosterPresence(const RosterItem &item, const string &resource, Presence::PresenceType presence, const string &msg)
{
}

void Dashboard::handleSelfPresence(const RosterItem &item, const string &resource, Presence::PresenceType presence, const string &msg)
{
}

bool Dashboard::handleSubscriptionRequest(const JID &jid, const string &msg)
{
}

bool Dashboard::handleUnsubscriptionRequest(const JID &jid, const string &msg)
{
}

void Dashboard::handleNonrosterPresence(const Presence &presence)
{
}

void Dashboard::handleRosterError(const IQ &iq)
{
}
