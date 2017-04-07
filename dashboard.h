#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QTableWidget>
#include <QLabel>
#include <QSqlDatabase>
#include <QDebug>
#include <iostream>
#include <string>
#include <QThread>
#include <QObject>
#include <QTextEdit>
#include <chatboxhandler.h>


#ifdef WIN32
#include <C:\Users\Steve\Downloads\gloox\src\client.h>
#include <C:\Users\Steve\Downloads\gloox\src\connectionlistener.h>
#include <C:\Users\Steve\Downloads\gloox\src\connectiontls.h>
#include <C:\Users\Steve\Downloads\gloox\src\connectiontcpclient.h>
#include <C:\Users\Steve\Downloads\gloox\src\vcardhandler.h>
#include <C:\Users\Steve\Downloads\gloox\src\vcardmanager.h>
#include <C:\Users\Steve\Downloads\gloox\src\rosterlistener.h>
#include <C:\Users\Steve\Downloads\gloox\src\rostermanager.h>
#include <C:\Users\Steve\Downloads\gloox\src\vcard.h>
#include <C:\Users\Steve\Downloads\gloox\src\messagehandler.h>
#include <C:\Users\Steve\Downloads\gloox\src\message.h>
#include <C:\Users\Steve\Downloads\gloox\src\mucroom.h>
#include <C:\Users\Steve\Downloads\gloox\src\mucroomhandler.h>
#else
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/connectiontls.h>
#include <gloox/connectiontcpclient.h>
#include <gloox/vcardhandler.h>
#include <gloox/vcardmanager.h>
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>
#include <gloox/vcard.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
// Group chat
#include <gloox/mucroom.h>
#include <gloox/mucroomhandler.h>
#endif
#include <QTextEdit>
#include <QEvent>
#include <QKeyEvent>

#ifdef WIN32
#include <windows.h>
#endif

namespace Ui {
class Dashboard;
}

using namespace gloox;
using namespace std;



class RecvThread : public QThread
{
    Q_OBJECT

public:
    RecvThread(Client *client)
    {
        this->client = client;
    }

    void stop()
    {
        running = false;
    }

    void run()
    {
        running = true;
        while (running)
        {
            //qDebug()<<"receiving ";
            client->recv(100);
            //qDebug()<<"recv done";
        }
    }

private:
    Client *client;
    bool running{false};
};


class Dashboard : public QMainWindow, ConnectionListener, VCardHandler, LogHandler, RosterListener, MessageHandler, MUCRoomHandler
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0, QString username = NULL, QString password = NULL);
    ~Dashboard();

    QSqlDatabase sqldb;

    void connClose(){

        sqldb.close();
        sqldb.removeDatabase(QSqlDatabase::defaultConnection);

    }

    bool connOpen(){

        sqldb = QSqlDatabase::addDatabase("QPSQL");
        sqldb.setHostName("localhost");
        sqldb.setDatabaseName("blastboard");
        sqldb.setUserName("postgres");
        sqldb.setPassword("password");
        sqldb.setPort(5432);

        bool ok = sqldb.open();

        return ok;
    }

    string getCurrentTime();
    void handleItemAdded(const JID &jid);
    void handleItemSubscribed(const JID &jid);
    void handleItemRemoved(const JID &jid);
    void handleItemUpdated(const JID &jid);
    void handleItemUnsubscribed(const JID &jid);
    void handleRoster(const Roster &roster);
    void handleRosterPresence(const RosterItem &item, const string &resource, Presence::PresenceType presence, const string &msg);
    void handleSelfPresence(const RosterItem &item, const string &resource, Presence::PresenceType presence, const string &msg);
    bool handleSubscriptionRequest(const JID &jid, const string &msg);
    bool handleUnsubscriptionRequest(const JID &jid, const string &msg);
    void handleNonrosterPresence(const Presence &presence);
    void handleRosterError(const IQ &iq);



private:

    // change these to be on the top bar widget only
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    int m_nMouseClick_X_Coordinate;
//    int m_nMouseClick_Y_Coordinate;
    //

    Ui::Dashboard *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *avatar;
    QProgressBar *pgbar;
    QTableWidget *vTable;
    QLabel *connection_error;


    virtual void onConnect();
    virtual void onDisconnect(ConnectionError e);
    virtual bool onTLSConnect(const CertInfo& info) {
        cout << "ConnListener::onTLSConnect()" << endl;
        return true;
    }
    virtual void handleLog( LogLevel level, LogArea area, const std::string& message );
    virtual void handleVCard( const JID& jid, const VCard *v );

    virtual void handleVCardResult( VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined  );
    virtual void handleMessage( const Message& stanza, MessageSession* session);

    void insertFriend(QString friendJid);


    virtual void handleMUCParticipantPresence(MUCRoom *room, const MUCRoomParticipant participant, const Presence &presence);
    virtual void handleMUCMessage(MUCRoom *room, const Message &msg, bool priv);
    virtual bool handleMUCRoomCreation(MUCRoom *room);
    virtual void handleMUCSubject(MUCRoom *room, const std::string &nick, const std::string &subject);
    virtual void handleMUCInviteDecline(MUCRoom *room, const JID &invitee, const std::string &reason);
    virtual void handleMUCError(MUCRoom *room, StanzaError error);
    virtual void handleMUCInfo(MUCRoom *room, int features, const std::string &name, const DataForm *infoForm);
    virtual void handleMUCItems(MUCRoom *room, const Disco::ItemList &items);

    JID jid;
    Client* client;
    RecvThread *recvThread;
    VCardManager *vcardManager;
    MUCRoom* m_room;



    // Group chat

//    void joinRoom( const std::string& room, const std::string& service, const std::string& nick );


public slots:
    void sendBlastMessage();
private slots:
    void blast_selected(QString username);
    void sendPrivateMessage();

    void sendBtnPress();
    void sendBtnRelease();
    void textChanged();
    void closeWindow();
    void minimizeWindow();
//    void expandWindow();


//    void joinRoom( const std::string& room, const std::string& service, const std::string& nick );


};


#endif // DASHBOARD_H
