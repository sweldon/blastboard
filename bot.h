#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

using namespace std;
using namespace gloox;

class ConnListener : public ConnectionListener {
public:

    virtual void onConnect() {
        cout << "Connected!" << endl;

    }
    virtual void onDisconnect(ConnectionError e) {
        cout << "Disconnected. " << e << endl;
    }
    virtual bool onTLSConnect(const CertInfo& info) {
        cout << "Connection is secure." << endl;
        return true;
    }
};

class Bot : public MessageHandler {
public:
    explicit Bot();
    ~Bot();

    virtual void handleMessage( const Message& stanza, MessageSession* session) {
        if(stanza.body() != ""){
            cout << stanza.from().username() << ": " << stanza.body() << endl;

            Message msg(Message::Chat, stanza.from(), "I received your message!" );
            client->send( msg );
        }

    }

private:
   Client *client;
   ConnListener *connListener;
};




#endif // BOT_H
