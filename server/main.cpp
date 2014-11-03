#include "Includes.h"


/******************************************************************************
 * Global Constants.
 *****************************************************************************/
const int MAXLEN = 1024;


struct Client
{
    TCPsocket sock;
    std::string _id;
    std::string _name;
    vec2d _position;
    vec2d _target_position;
    vec2d _velocity;
    Direction _facing;

    std::string serialize()
    {
        std::ostringstream ret_stream;
        ret_stream << _id << ' ' << _position.get_x() << ' ' << _position.get_y()
                   << _target_position.get_x() << ' ' << _target_position.get_y() << ' '
                   << _velocity.get_x() << ' ' << _velocity.get_y() << ' '
                   << _facing << ' ';
        return ret_stream.str();
    }

    void deserialize(std::string serialized)
    {
        std::istringstream in_stream(serialized);
        int facing;
        double px, py, tx, ty, vx, vy;
        in_stream >> _id >> px >> py >> tx >> ty >> vx >> vy >> facing;
        _position.set_x(px);
        _position.set_y(py);
        _target_position.set_x(px);
        _target_position.set_y(py);
        _velocity.set_x(vx);
        _velocity.set_y(vy);
        _facing = static_cast< Direction >(facing);
    }
};


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
    return SDLNet_TCP_Send(sock, buff, MAXLEN);
}


// Converts a float to string
std::string ftos(float f)
{
	std::ostringstream buff;
	buff << f;

	return buff.str();
}


// Converts an integer to string
std::string itos(int i)
{
	std::ostringstream buff;
	buff << i;

	return buff.str();
}


/******************************************************************************
 * Global Variables.
 *****************************************************************************/
std::vector<Client> clients;
int num_clients=0;
TCPsocket server;
void send_client(int, std::string);
void send_all(std::string buf);
void add_client(TCPsocket sock, std::string name);


/* find a client in our array of clients by it's socket. */
/* the socket is always unique */
int find_client(TCPsocket sock)
{
	for(int i = 0; i < num_clients; i++)
		if(clients[i].sock == sock)
			return(i);

    return -1;
}


/* find a client in our array of clients by it's name. */
/* the name is always unique */
int find_client_name(std::string name)
{
	for(int i=0; i < num_clients;i++)
		if (clients[i].name == name)
			return i;
		
	return -1;
}


// Handles logging in
void handle_login(TCPsocket sock, std::string name, std::string password)
{
    if(!name.length())
	{
		send_message("User not found.", sock);
		SDLNet_TCP_Close(sock);
		return;
	}

    int cindex = find_client_name(name);

    if (cindex == -1)
    {
        add_client(sock, name);
        return;
    }
    
    if (clients[cindex].active)
    {
        send_message("User already logged in.", sock);
        SDLNet_TCP_Close(sock);
        return;
    }

    clients[cindex].sock = sock;
    clients[cindex].active = true;
    return;
}


// Add a client to the list of clients
void add_client(TCPsocket sock, std::string name)
{	
	Client c;

	c.name = name;
	c.sock = sock;
	c.x = rand() % W;
	c.y = rand() % H;
    c.active = true;

	clients.push_back(c);

	num_clients++;

	// std::cout << "inside add client" << std::endl;
// 	std::cout << "num clients: " << num_clients << std::endl;

	// Send an acknowledgement
    std::string success = "Login Successful."
	// send client their player number
	send_client(num_clients - 1, player_number);
}


/* closes the socket of a disconnected client */
void handle_disconnect(int i)
{
	std::string name=clients[i].name;

	if(i<0 || i>=num_clients)
		return;
	
	/* close the old socket, even if it's dead... */
	SDLNet_TCP_Close(clients[i].sock);
    clients[i].active = false;
    //std::cout << "Removed client # " << i << std::endl;
    //std::cin.ignore();
}


/* Reconnects a client */
void reconnect_client(std::string name, std::string password)
{
    clients[find_client_name(name)].active = true;
    // pass for now
}


/* create a socket set that has the server socket and all the client sockets */
SDLNet_SocketSet create_sockset()
{
	static SDLNet_SocketSet set=NULL;

	if(set)
		SDLNet_FreeSocketSet(set);
	set = SDLNet_AllocSocketSet(num_clients + 1);
	if(!set)
    {
        std::cerr << "SDLNet_AllocSocketSet: " << SDLNet_GetError() << std::endl;
        return 0;
	}
	SDLNet_TCP_AddSocket(set, server);
	for(int i=0; i < num_clients; i++)
        if (clients[i].active)
            SDLNet_TCP_AddSocket(set, clients[i].sock);
	return(set);
}


/* send a buffer to all clients */
void send_all(std::string buf)
{
	if(buf == "" || num_clients == 0)
		return;
    
    for (int i = 0; i < num_clients; i++)
	{
		if(!send_message(buf, clients[i].sock))
        {
            std::cout << "errr what \n";
            handle_disconnect(i);
        }
	}
}


// Send a string to a particular client
void send_client(int i, std::string buf)
{
	if (buf == "")
        return;

	send_message(buf, clients[i].sock);
}


// Generate the string to be sent or something
std::string generate_string_for_clients()
{
    std::ostringstream ret;

    ret << num_clients << ' ';
    for (int i = 0; i < num_clients; i++)
    {
        ret << clients[i].serialize();
	}

    return ret.str();
}


void update_data(int i, std::string message)
{
    clients[i].deserialize(message);
}


// Point of entry
int main(int argc, char **argv)
{
	IPaddress ip;
	TCPsocket sock;
	SDLNet_SocketSet set;
	
	std::string message;
	
	Uint32 ipaddr;
	Uint16 port;
	
	/* check our commandline */
	if(argc < 2)
	{
		std::cout << argv[0] << "port\n";
		exit(0);
	}
	
	/* initialize SDL */
	if(SDL_Init(0)==-1)
	{
		//printf("SDL_Init: %s\n",SDL_GetError());
		std::cout << "ERROR" << std::endl;
		exit(1);
	}

	/* initialize SDL_net */
	if(SDLNet_Init()==-1)
	{
		//printf("SDLNet_Init: %s\n",SDLNet_GetError());
		std::cout << "ERROR" << std::endl;
		SDL_Quit();
		exit(2);
	}

	/* get the port from the commandline */
	port=(Uint16)strtol(argv[1],NULL,0);

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost(&ip,NULL,port)==-1)
	{
		std::cout << "SDLNet_ResolveHost: ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		exit(3);
	}

	/* open the server socket */
	server=SDLNet_TCP_Open(&ip);
	if(!server)
	{
		std::cout << "SDLNet_TCP_Open ERROR" << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		exit(4);
	}

	while(1)
	{
		int numready;
        //std::cout << "HERE " << std::endl;
		set = create_sockset();
        //std::cout << "ALSO HERE " << std::endl;
		numready = SDLNet_CheckSockets(set, (Uint32)1000);
        //std::cout << "Numready " << numready << std::endl;
		if(numready == -1)
		{
			std::cout << "SDLNet_CheckSockets ERROR" << std::endl;
			break;
		}
        
		if(numready == 0)
			continue;
        
		if(SDLNet_SocketReady(server))
		{
			numready--;

			sock=SDLNet_TCP_Accept(server);
			if(sock)
			{
				std::string name;
                
				name = recv_message(sock);
				std::cout << "name: " << name << std::endl;

                handle_login(sock,name);
            }
            else
                SDLNet_TCP_Close(sock);
		}


		//---------------------------------------------------------------------
		// LOOP THROUGH CLIENTS
		//---------------------------------------------------------------------
		for(int i = 0; numready > 0 && i < num_clients; i++)
		{
			message = "";
            if (clients[i].state == ACTIVE)
            {
                if(SDLNet_SocketReady(clients[i].sock))
                {
                    //---------------------------------------------------------
                    // GET DATA FROM CLIENT
                    //---------------------------------------------------------
                    message = recv_message(clients[i].sock);
                    
                    if(message > "") 
                        update_data(i, message);
                    
                    numready--;
                }
            }
        }
        
        send_all(generate_string_for_clients());
	}
    
	/* shutdown SDL_net */
	SDLNet_Quit();

	/* shutdown SDL */
	SDL_Quit();

	return(0);
}

