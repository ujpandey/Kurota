/******************************************************************************
 * This is the client side of the Space Shooter project for CISS465
 *****************************************************************************/


/******************************************************************************
 * BEGIN Includes.
 *****************************************************************************/

// Standard includes
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// SDL wrapper from Dr. Liow
#include "Includes.h"
#include "Event.h"
#include "compgeom.h"
#include "Constants.h"
#include "Surface.h"

// SDL net
#include "SDL_net.h"


/******************************************************************************
 * END Includes.
 *****************************************************************************/


/******************************************************************************
 * Class definitions.
 *****************************************************************************/
class Player
{
public:
	Player(float x1, float y1, int num=-1, int state=0)
		: x(x1), y(y1), size(10.0), number(num), status(state)
	{
        switch(num)
        {
            case 0:
                color[0] = 255;
                color[1] = 0;
                color[2] = 0;
                break;

            case 1:
                color[0] = 0;
                color[1] = 255;
                color[2] = 0;
                break;

            case 2:
                color[0] = 0;
                color[1] = 0;
                color[2] = 255;
                break;

            case 3:
                color[0] = 255;
                color[1] = 255;
                color[2] = 0;
                break;
                
            case 4:
                color[0] = 255;
                color[1] = 0;
                color[2] = 255;
                break;

            case 5:
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                break;

            case 6:
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                break;

            default:
                color[0] = 255 / 10;
                color[1] = 255 / 5;
                color[2] = 255 / 2.5;
        }
	}
    
    float x, y, size;
	int number, status;
    float color[3];
};


/******************************************************************************
 * Global Constants.
 *****************************************************************************/
const int MAXLEN = 1024;


/******************************************************************************
 * Global Variables.
 *****************************************************************************/
std::vector<Player> players;
SDL_Thread *net_thread=NULL, *local_thread=NULL;
int player_number = -1;


/******************************************************************************
 * Functions
 *****************************************************************************/
// Receive a string over TCP/IP
std::string recv_message(TCPsocket sock)
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
int send_message(std::string msg, TCPsocket sock)
{
    char * buff = (char *)msg.c_str();      
    SDLNet_TCP_Send(sock, buff, MAXLEN);

    return 1;
}


void parse_player_data(std::string message)
{
    std::stringstream message_stream(message);

    int num_players = 0, _status = 0;
    float _x, _y;
    
    message_stream >> num_players;
    
	for (int i = 0; i < num_players; i++)
    {
        if (i < players.size())
        {
            message_stream >> players[i].x >> players[i].y >> players[i].status;
        }
        
        else
        {
            message_stream >> _x >> _y >> _status;

            Player player(_x, _y, i, _status);
            players.push_back(player);
        }
	}		
}


void recv_player_number(std::string message)
{
	int i = 0;
	std::string temp_num = "";

	if (message[0] == 'N')
    {
		i++;
		while (message[i] != ';')
        {
			temp_num += message[i];
			i++;
		}
	}

	player_number = atoi(temp_num.c_str());
}


int main(int argc, char **argv)
{
	IPaddress ip;
	TCPsocket sock;
  
	int numready;
	Uint16 port;
	SDLNet_SocketSet set;	

	std::string name;
	std::string to_server;
	std::string from_server;

	/* check our commandline */
	if(argc < 4)
	{
		std::cout << "Usage: " << argv[0] << " host_ip host_port username" << std::endl;
		return 0;
	}
	
	name = argv[3];
	
	/* initialize SDL */
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL_Init ERROR" << std::endl;
		return 0;
	}

	/* initialize SDL_net */
	if(SDLNet_Init() == -1)
	{
		std::cout << "SDLNet_Init ERROR" << std::endl;
		SDL_Quit();
		return 0;
	}

	set = SDLNet_AllocSocketSet(1);
	if(!set)
	{
		std::cout << "SDLNet_AllocSocketSet ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		return 0;
	}

	/* get the port from the commandline */
	port = (Uint16)strtol(argv[2],NULL,0);
	
	/* Resolve the argument into an IPaddress type */
	std::cout << "connecting to " << argv[1] << " port " << port << std::endl;

	if(SDLNet_ResolveHost(&ip,argv[1],port) == -1)
	{
		std::cout << "SDLNet_ResolveHost ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		return 0;
	}

	/* open the server socket */
	sock=SDLNet_TCP_Open(&ip);
	if(!sock)
	{
		std::cout << "SDLNet_TCP_Open ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		return 0;
	}
	
	if(SDLNet_TCP_AddSocket(set,sock)==-1)
	{
		std::cout << "SDLNet_TCP_AddSocket ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		return 0;
	}

	send_message(name, sock);

	std::cout << "Logged in as: " << name << std::endl;
	
	recv_player_number(recv_message(sock));

	std::cout << "player num: " << player_number << std::endl;

	//-------------------------------------------------------------------------
	// GAME SEGMENT
	//-------------------------------------------------------------------------
	Surface surface(W, H);
	Event event;

	while(1)
	{
        std::cout << "players.size() is " << players.size() << std::endl;
		numready=SDLNet_CheckSockets(set, 100);
        if(numready == -1)
		{
			std::cout << "SDLNet_CheckSockets ERROR" << std::endl;
			break;
		}

		//-------------------------------------------------------------------------------
		// GET DATA FROM SERVER
		//-------------------------------------------------------------------------------
		from_server = "";
		if(numready && SDLNet_SocketReady(sock))
		{
			from_server = recv_message(sock);
            std::cout << from_server << std::endl;

            parse_player_data(from_server);
		}

		if (event.poll() && event.type() == QUIT) break;

		KeyPressed keypressed = get_keypressed();

		to_server = "";
		if (keypressed[UPARROW])
        {
			to_server = "1";
			send_message(to_server, sock);
		}
		else if (keypressed[DOWNARROW])
        {
			to_server = "2";
			send_message(to_server, sock);
		}
		else if (keypressed[LEFTARROW])
        {
			to_server = "3";
			send_message(to_server, sock);
		}
		else if (keypressed[RIGHTARROW])
        {
			to_server = "4";
			send_message(to_server, sock);
		}

		surface.fill(WHITE);

		for (int i = 0; i < players.size(); i++)
        {
            if (players[i].status)
            {
                surface.lock();
                surface.put_rect(players[i].x, players[i].y,
                                 players[i].size, players[i].size,
                                 players[i].color[0],
                                 players[i].color[1],
                                 players[i].color[2]);
                surface.unlock();
            }
        }

		surface.flip();


		delay(1);
	}

	SDLNet_Quit();
	SDL_Quit();

	return(0);
}
