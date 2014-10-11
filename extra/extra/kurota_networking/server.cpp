#include <iostream>
#include <cstring>
#include "SDL.h"
#include "SDL_net.h"


typedef char Message[1024];


int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();

    // Allocate memory for the server's ip
	IPaddress ip;

    // NULL is used here because we want to be the server.
   	SDLNet_ResolveHost(&ip, NULL, 1234);

	// Create Server Socket (TCP) that listens for incoming connections
	TCPsocket server = SDLNet_TCP_Open(&ip);

    // This is the socket that will accept connections and transfer data
	TCPsocket client;

    // This is the message that we will send to the clients
	Message to_client = "HELLO CLIENT!";

    // This is the message that we will receive data into from the clients
    Message from_client;

    while(1)
	{
        // Attempt to accept incoming connection from client
		client = SDLNet_TCP_Accept(server);

		if (client)
		{
			// Send message to client
            SDLNet_TCP_Send(client, to_client, strlen(to_client) + 1);

            // Receive message from client
            SDLNet_TCP_Recv(client, from_client, 100);
            std::cout << from_client << std::endl;

            // Close the socket
            SDLNet_TCP_Close(client);

            // Quit
			break;
		}
	}

    // Close the socket. .
	SDLNet_TCP_Close(server); 

    // Quit SDL and SDLNet
	SDLNet_Quit();
	SDL_Quit();

	return 0;
}
