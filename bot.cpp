//A basic gloox tutorial by Anders Schau Knatten
//Read more at http://blog.knatten.org/2012/03/23/basic-gloox-tutorial/
//To compile on Linux: g++ -o bot bot.cpp -lgloox -lpthread
#include "bot.h"

using namespace std;
using namespace gloox;


Bot::Bot() {

    JID jid("bot@earthworkx.com");
    client = new Client( jid, "botpw" );
    connListener = new ConnListener();
    client->registerMessageHandler( this );
    client->registerConnectionListener(connListener);
    client->connect(true);



};

Bot::~Bot() {
    delete client;
    delete connListener;
}
