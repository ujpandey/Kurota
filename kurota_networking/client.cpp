#include <iostream>
#include "SDL.h"
#include "SDL_net.h"
#include <cstring>

typedef char Message[1024];

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;

    SDLNet_ResolveHost(&ip,"bilbo.ccis.edu", 1234);

    TCPsocket server = SDLNet_TCP_Open(&ip);

    Message to_server = "Hello Server!";

    Message from_server;

    if(server)
    {
        // Sending message to the client
        SDLNet_TCP_Send(server, to_server, strlen(to_server) + 1);

        // Receiving message from the client
        SDLNet_TCP_Recv(server, from_server, 100);

        // Closing the socket
        SDLNet_TCP_Close(server);

    }

    // Quit SDL and SDLNet
    SDLNet_Quit;
    SDL_Quit();

    return 0;
}
