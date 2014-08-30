#include "Network.h"

NetworkManager * NetworkManager::instance = NULL;

NetworkManager * NetworkManager::get_instance()
{
    if (instance)
        return instance;
    instance = new NetworkManager;
    return instance;
}

NetworkManager::NetworkManager()
{
}

void NetworkManager::init(const char * hostaddr)
{
/* initialize SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std:: endl;
        exit(0);
    }
/* initialize SDL_net */
    if(SDLNet_Init() == -1)
    {
        std::cerr << "SDLNet_Init ERROR: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    set = SDLNet_AllocSocketSet(1);
    if(!set)
    {
        std::cerr << "SDLNet_AllocSocketSet ERROR: "
                  << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        exit(2);
    }
/* Resolve the argument into an IPaddress type */
    std::cout << "connecting to " << hostaddr << " port " << port << std::endl;
    if(SDLNet_ResolveHost(&ip, hostaddr, port) == -1)
    {
        std::cerr << "SDLNet_ResolveHost ERROR: "
                  << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        exit(3);
    }
}

void NetworkManager::connect()
{
    /* open the server socket */
    sock=SDLNet_TCP_Open(&ip);
    if(!sock)
    {
        std::cerr << "SDLNet_TCP_Open ERROR: "
                  << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        exit(4);
    }
    if(SDLNet_TCP_AddSocket(set, sock) == -1)
    {
        std::cerr << "SDLNet_TCP_AddSocket ERROR: "
                  << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        exit(5);
    }
}

void NetworkManager::disconnect()
{
    if (SDLNet_TCP_DelSocket(set, sock) == -1)
    {
        std::cerr << "SDLNet_DelSocket error: "
                  << SDLNet_GetError() << std::endl;

        exit (-1);
    }
}

// Receive a string over TCP/IP
std::string NetworkManager::recv_message(TCPsocket sock)
{
    char buff[MAXLEN] = {' '};
    SDLNet_TCP_Recv(sock, buff, MAXLEN);

    if (buff == NULL)
    {
        std::string ret = "";
        return ret;
    }
    
    std::string ret(buff, strlen(buff));
    return ret;
}

// Send a string over TCP/IP
int NetworkManager::send_message(const std::string & msg, TCPsocket sock)
{
    char * buff = (char *)msg.c_str();      
    return SDLNet_TCP_Send(sock, buff, MAXLEN);
}

std::string NetworkManager::listen()
{
    numready=SDLNet_CheckSockets(set, (Uint32)10);
    if(numready == -1)
    {
        std::cerr << "SDLNet_CheckSockets ERROR: "
                  << SDLNet_GetError() << std::endl;
        exit(5);
    }
//-------------------------------------------------------------------------------
// GET DATA FROM SERVER
//-------------------------------------------------------------------------------
    from_server = "";
    if(numready && SDLNet_SocketReady(sock))
    {
        from_server = recv_message(sock);
        std::cout << "from_server: " << from_server << std::endl;
// unpack(from_server);
    }
    return from_server;
}

void NetworkManager::say(const std::string & msg)
{
    if (!send_message(msg, sock))
    {
        disconnect();
        connect();
        listen();
        send_message(msg, sock);
    }
}
