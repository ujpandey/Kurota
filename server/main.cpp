#include "Includes.h"
#include "GameObject.h"


/******************************************************************************
 * Global Constants.
 *****************************************************************************/
const int MAXLEN = 1024;


class Client
{
public:
    Client()
        : sock(NULL), active(false), _id(""), _password(""),
          _hp(100), _mana(100), _position(vec2d(0,0)),
          _target_position(vec2d(0,0)), _velocity(vec2d(0,0)), _facing(SOUTH)
    {}
           
    TCPsocket sock;
    bool active;
    std::string _id;
    std::string _password;
    int _hp;
    int _mana;
    vec2d _position;
    vec2d _target_position;
    vec2d _velocity;
    Direction _facing;

    const std::string serialize() const
    {
        std::ostringstream ret_stream;
        std::cout << "Pussy" << std::endl;
        ret_stream << _id << ' ' << _hp << ' ' << _mana << ' '
                   << _position.get_x() << ' ' << _position.get_y()
                   << _target_position.get_x() << ' ' << _target_position.get_y() << ' '
                   << _velocity.get_x() << ' ' << _velocity.get_y() << ' '
                   << _facing << ' ';
        std::cout << "Bitch." << std::endl;
        return ret_stream.str();
    }

    void deserialize(const std::string & serialized)
    {
        std::istringstream in_stream(serialized);
        int facing;
        double px, py, tx, ty, vx, vy;
        in_stream >> _id >> _hp >> _mana >> px >> py >> tx >> ty >> vx >> vy >> facing;
        _position.set_x(px);
        _position.set_y(py);
        _target_position.set_x(tx);
        _target_position.set_y(ty);
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
std::vector<Client *> clients;
int num_clients=0;
TCPsocket server;

// Load registered clients from file
void load_clients(const std::string & file_name="clients.db")
{
    std::fstream fs;
    fs.open(file_name.c_str(), std::fstream::in);
    if (fs.is_open())
    {
        std::string input;
        while (std::getline(fs, input))
        {
            if (input == "")
                break;
            std::cout << input << std::endl;

            std::istringstream in_stream(input);

            Client * c = new Client;

            int facing;
            double px, py;

            in_stream >> c -> _id >> c -> _password >> c -> _hp >> c -> _mana >> px >> py;
            c -> _position.set_x(px);
            c -> _position.set_y(py);

            clients.push_back(c);

            num_clients++;
        }
        fs.close();
    }
}

void print_clients()
{
    for (int i = 0; i < clients.size(); ++i)
    {
        std::cout << i << ' ' << clients[i] -> _id << ' ' << clients[i] -> _password << std::endl;
    }
}

// Write clients to file
void dump_clients(const std::string & filename="clients.db")
{
    //std::cout << "Hey bro." << std::endl;
    std::ofstream fs;
    fs.open(filename.c_str(), std::fstream::out);
    if (!fs.is_open())
    {
        std::cout << "Couldn't open the file." << std::endl;
        fs.close();
        return;
    }
    for (int i = 0; i < clients.size(); ++i)
    {
        fs << clients[i] -> _id << ' ' << clients[i] -> _password << ' '
           << clients[i] -> _hp << ' ' << clients[i] -> _mana << ' '
           << clients[i] -> _position.get_x() << ' ' << clients[i] -> _position.get_y()
           << ' ' << '\n';
    }
    fs.close();
}

void send_client(int, std::string);
void send_all(std::string buf);
void add_client(TCPsocket sock, std::string id, std::string password);
void reconnect_client(TCPsocket sock, const int & c_index);


/* find a client in our array of clients by it's socket. */
/* the socket is always unique */
int find_client(TCPsocket sock)
{
	for(int i = 0; i < num_clients; i++)
		if(clients[i] -> sock == sock)
			return(i);

    return -1;
}


/* find a client in our array of clients by it's id. */
/* the id is always unique */
int find_client_id(std::string id)
{
	for(int i=0; i < clients.size();i++)
    {
		if (clients[i] -> _id == id)
			return i;
    }
	return -1;
}


// Handles logging in
void handle_login(TCPsocket sock, std::string id, std::string password)
{
//     if(!id.length())
// 	{
// 		send_message("User not found.", sock);
// 		SDLNet_TCP_Close(sock);
// 		return;
// 	}

    int c_index = find_client_id(id);

    if (c_index == -1)
    {
        send_message("User not found.", sock);
        SDLNet_TCP_Close(sock);
    }
    else if (clients[c_index] -> active)
    {
        send_message("User already logged in.", sock);
        SDLNet_TCP_Close(sock);
    }
    else if (clients[c_index] -> _password != password)
    {
        send_message("Wrong Password.", sock);
        SDLNet_TCP_Close(sock);
    }
    else
    {
        std::cout << "Forwarding to reconnect client." << std::endl;
        reconnect_client(sock, c_index);
    }
    
    return;
}

// Handle registration
void handle_registration(TCPsocket sock, std::string id, std::string password)
{
//     if(!id.length())
// 	{
// 		send_message("User not found.", sock);
// 		SDLNet_TCP_Close(sock);
// 		return;
// 	}

    int c_index = find_client_id(id);

    if (c_index == -1)
    {
        //std::cout << "hey baby" << std::endl;
        add_client(sock, id, password);
    }
    else
    {
        send_message("User already exists.", sock);
        SDLNet_TCP_Close(sock);
    }

    return;
}


// Add a client to the list of clients
void add_client(TCPsocket sock, std::string id, std::string password)
{	
	Client * c = new Client;

	c -> _id = id;
    c -> _password = password;
	c -> sock = sock;
	c -> _position.set_x(rand() % 600);
	c -> _position.set_y(rand() % 600);

	clients.push_back(c);

    send_message("success", sock);
    SDLNet_TCP_Close(sock);
	// std::cout << "inside add client" << std::endl;
// 	std::cout << "num clients: " << num_clients << std::endl;

    //dump_clients();
	// Send an acknowledgement
}


/* closes the socket of a disconnected client */
void handle_disconnect(int i)
{
	std::string id=clients[i] -> _id;

	if(i<0 || i>=num_clients)
		return;
	
	/* close the old socket, even if it's dead... */
	SDLNet_TCP_Close(clients[i] -> sock);
    clients[i] -> active = false;
    //std::cout << "Removed client # " << i << std::endl;
    //std::cin.ignore();
}


/* Reconnects a client */
void reconnect_client(TCPsocket sock, const int & c_index)
{
    clients[c_index] -> active = true;
    clients[c_index] -> sock = sock;
	// send client their player number
    std::cout << "Forwarding to send_client." << std::endl;
	send_client(c_index, "success");
    std::cout << "Returned from send_client." << std::endl;
    num_clients++;
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
        if (clients[i] -> active)
            SDLNet_TCP_AddSocket(set, clients[i] -> sock);
	return(set);
}


/* send a buffer to all clients */
void send_all(std::string buf)
{
	if(buf == "" || num_clients == 0)
		return;
    
    for (int i = 0; i < num_clients; i++)
	{
		if(!send_message(buf, clients[i] -> sock))
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

	send_message(buf, clients[i] -> sock);
}


// Generate the string to be sent or something
std::string generate_string_for_clients()
{
    std::ostringstream ret;

    ret << num_clients << ' ';
    for (int i = 0; i < num_clients; i++)
    {
        ret << clients[i] -> serialize();
	}

    return ret.str();
}


void update_data(int i, std::string message)
{
    clients[i] -> deserialize(message);
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
		std::cout << argv[0] << " port\n";
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

    //load_clients();
    print_clients();
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
				std::string from_client;
                
				from_client = recv_message(sock);

                char head = from_client[0];

                from_client.erase(from_client.begin());

                std::istringstream bleh(from_client);

                std::string id, password;

                bleh >> id >> password;
                std::cout << "id: " << id << " password: " << password << std::endl;

                if (head == 'R')
                    handle_registration(sock, id, password);
                else if (head == 'L')
                    handle_login(sock, id, password);
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
            if (clients[i] -> active)
            {
                if(SDLNet_SocketReady(clients[i] -> sock))
                {
                    //---------------------------------------------------------
                    // GET DATA FROM CLIENT
                    //---------------------------------------------------------
                    message = recv_message(clients[i] -> sock);
                    
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

