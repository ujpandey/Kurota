#ifndef NETWORK_H
#define NETWORK_H

#include "Includes.h"

const int MAXLEN = 1024;

class NetworkManager
{
public:
    static NetworkManager * get_instance();
    
    void init(const char * hostaddr);
    
    void connect();
    void disconnect();
    
    std::string listen();
    void say(const std::string & msg);

    // Network stuff
    IPaddress ip;
    Uint16 port;
    TCPsocket sock;
    int numready;
    SDLNet_SocketSet set;	
// Buffers for communication with server
    std::string to_server;
    std::string from_server;

private:
    static NetworkManager * instance;

    NetworkManager();
    std::string recv_message(TCPsocket sock);
    int send_message(const std::string & msg, TCPsocket sock);
};
    
#endif
