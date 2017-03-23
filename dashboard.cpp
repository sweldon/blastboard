#include "dashboard.h"
#include "ui_dashboard.h"
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QtSql>
#include <ctime>
#include <QToolBar>
#include <QStyle>
#include <QDesktopWidget>


using namespace std;

Dashboard::Dashboard(QWidget *parent, QString un, QString pw) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{

    this->setWindowFlags(Qt::FramelessWindowHint);

    this->statusBar()->setVisible(false);



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
    JID jid( username + "@earthworkx.com" );
    client = new Client( jid, password);
    client->registerConnectionListener( this );
    client->setPresence( Presence::Available, -1 );
    client->disco()->setVersion( "gloox muc_example", GLOOX_VERSION, "Linux" );
    client->disco()->setIdentity( "client", "bot" );
    client->setCompression( false );
    StringList ca;
    ca.push_back( "/path/to/cacert.crt" );
    client->setCACerts( ca );

    client->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

    JID nick( "blastchat@conference.earthworkx.com/"+username );
    m_room = new MUCRoom( client, nick, this, 0 );
    recvThread = new RecvThread(client);
    recvThread->start();
    client->connect(false);

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
    connect(ui->sendMsgBtn, SIGNAL(clicked(bool)), this, SLOT(sendBlastMessage()));
    connect(ui->sendMsgBtn, SIGNAL(pressed()), this, SLOT(sendBtnPress()));
    connect(ui->sendMsgBtn, SIGNAL(released()), this, SLOT(sendBtnRelease()));
    connect(ui->messageDraft, SIGNAL(textChanged()), this, SLOT(textChanged()));

    // QObject::connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(blast_selected(username)));



}


Dashboard::~Dashboard()
{
    recvThread->stop();
    delete ui;
}

void Dashboard::textChanged(){
    QString msg = ui->messageDraft->toPlainText().trimmed();
    if(msg!=""){
        ui->sendMsgBtn->setStyleSheet("background-color:#494a4a;border:none;");
    }
    else{
        ui->sendMsgBtn->setStyleSheet("background-color:#2f3030; border:none;");
    }

}

void Dashboard::sendBtnPress(){
    ui->sendMsgBtn->setStyleSheet("background-color:#494a4a;border:none;");
}
void Dashboard::sendBtnRelease(){
    ui->sendMsgBtn->setStyleSheet("background-color:#2f3030; border:none;");
}

void Dashboard::sendBlastMessage(){

    QString msg = ui->messageDraft->toPlainText().trimmed();
    if(msg!=""){
        string ptmsg = msg.toUtf8().constData();
        m_room->send( ptmsg );
        ui->messageDraft->setText("");
    }
    else{
        ui->messageDraft->setText("");
    }

}

void Dashboard::sendPrivateMessage(){
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


                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);
                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);
                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);
                        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/assets/avatar_sample.png"),username));
                        ui->statusList->addItem(status);
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
//    vcardManager->fetchVCard(jid.bare(), this);
    m_room->join();
    m_room->getRoomInfo();
    m_room->getRoomItems();
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

// Group chat

void Dashboard::handleMUCParticipantPresence( MUCRoom * /*room*/, const MUCRoomParticipant participant,
                                        const Presence& presence )
{
  if( presence.presence() == Presence::Available )
    printf( "%s is in the room, too\n", participant.nick->resource().c_str() );
  else if( presence.presence() == Presence::Unavailable )
    printf( " %s left the room\n", participant.nick->resource().c_str() );
  else
    printf( "Presence is %d of %s\n", presence.presence(), participant.nick->resource().c_str() );
}

void Dashboard::handleMUCMessage( MUCRoom* /*room*/, const Message& msg, bool priv )
{
  printf( "%s said: '%s' (history: %s, private: %s)\n", msg.from().resource().c_str(), msg.body().c_str(),
          msg.when() ? "yes" : "no", priv ? "yes" : "no" );

  bool old = (msg.when() ? "yes" : "no") == "yes";


  if(msg.body() != "" && old ==0){
    QString body = QString::fromStdString(msg.body().c_str());
    QString sender = QString::fromStdString(msg.from().resource().c_str());
    // only retrievable if old == 1:
    // QString time = QString::fromStdString(msg.when()->stamp());

   QString timestamp = QString::fromStdString(getCurrentTime());

    ui->chatDialog->append(timestamp+" - <b>"+sender+"</b>: "+body);


  }



}

string Dashboard::getCurrentTime(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int hour = now->tm_hour;
    int min = now->tm_min;

    bool pm_flag = false;
    if(hour > 12){
        hour -= 12;
        pm_flag = true;
    }
    std::string str_min = std::to_string(min);
    if(min < 10){
        str_min.insert(0, "0");
    }

    std::string timestamp = std::to_string(hour)+":"+str_min;

    if(pm_flag){
        timestamp += " PM";
    }else{
        timestamp += " AM";
    }
    return timestamp;
}

void Dashboard::handleMUCSubject( MUCRoom * /*room*/, const std::string& nick, const std::string& subject )
{
  if( nick.empty() )
    printf( "Subject: %s\n", subject.c_str() );
  else
    printf( "%s has set the subject to: '%s'\n", nick.c_str(), subject.c_str() );
}

void Dashboard::handleMUCError( MUCRoom * /*room*/, StanzaError error )
{
  printf( "!!!!!!!!got an error: %d", error );
}

void Dashboard::handleMUCInfo( MUCRoom * /*room*/, int features, const std::string& name,
                                const DataForm* infoForm )
{
  printf( "features: %d, name: %s, form xml: %s\n",
          features, name.c_str(), infoForm->tag()->xml().c_str() );
}

void Dashboard::handleMUCItems( MUCRoom * /*room*/, const Disco::ItemList& items )
{
    // show users online
  Disco::ItemList::const_iterator it = items.begin();
  for( ; it != items.end(); ++it )
  {
    printf( "%s -- %s is an item here\n", (*it)->jid().full().c_str(), (*it)->name().c_str() );
  }
}

void Dashboard::handleMUCInviteDecline( MUCRoom * /*room*/, const JID& invitee, const std::string& reason )
{
  printf( "Invitee %s declined invitation. reason given: %s\n", invitee.full().c_str(), reason.c_str() );
}

bool Dashboard::handleMUCRoomCreation( MUCRoom *room )
{
  printf( "room %s didn't exist, beeing created.\n", room->name().c_str() );
  return true;
}

// change these to be on the top bar widget only
void Dashboard::mousePressEvent(QMouseEvent *event) {
m_nMouseClick_X_Coordinate = event->x();
m_nMouseClick_Y_Coordinate = event->y();
}

void Dashboard::mouseMoveEvent(QMouseEvent *event) {
move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
//
