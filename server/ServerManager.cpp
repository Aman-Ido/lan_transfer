/* 
this file will hold nothing more just a server manager class that will hand opening or closing of the server
*/
class ServerManager {
	public:
		UDPsocket l_socket = nullptr; // local socket
		std::string socket_type = "server"; // type of the socket (default" server" / but can be set to client)
		int server_port = 4000; // default server port
		std::string server_address = "127.0.0.1"; // local host
		IPaddress server_ip = {0}; // this is the server ip / to store the server ip
		
		// methods
			// method to clear the socket (free_socket)
			void free_socket () {
				if (this -> l_socket != nullptr) {
					SDLNet_UDP_Close (this -> l_socket);
					this -> l_socket = nullptr;
				}
			}
			
			// method to open the port as per the socket type
			bool create_socket () {
				free_socket (); // freeing the previous socket if exists
				
				
				// if the socke type is "server" then we port the port 
				if (this -> socket_type == "server") {
					if (SDLNet_ResolveHost (&this -> server_ip, nullptr, this -> server_port) < 0) {
						std::cerr << "Could not resolve host : " << SDLNet_GetError () << std::endl; 
						return false;
					} else {
						std::cout << "Server : Resolved Host" << std::endl;
					}
					
					// opening the socket
					this -> l_socket = SDLNet_UDP_Open (this -> server_port);
					if (this -> l_socket == nullptr) {
						std::cerr << "SDLNet_UDP_Open : " << SDLNet_GetError () << std::endl;
						return false;
					} else {
						std::cout << "Server : Socket Opened at " << this -> server_port << std::endl;
					}
				} else if (this -> socket_type == "client") { // but if the socket type is "client" we do resolve host 
				// and then we will open the port
					
					// opening the port
					this -> l_socket = SDLNet_UDP_Open (0); 
					if (this -> l_socket == nullptr) {
						std::cerr << "SDLNet_UDP_Open : " << SDLNet_GetError () << std::endl;
						return false;
					} else { 
						std::cout << "Client : Socket Opened " << std::endl;
						
						
					}
					// resolving host
					if (SDLNet_ResolveHost (&this -> server_ip, this -> server_address.c_str(), this -> server_port) < 0) {
						std::cerr << "SDLNet_ResolveHost : " << SDLNet_GetError () << std::endl;
						return false;
					} else {
						// std::cout << "Client : Host Resolved at " << this -> server_ip << ", " << this -> server_port << std::endl;
						std::cout << "Client : Host Resolved at " << this -> server_ip.host << ", " << this -> server_ip.port  << std::endl;
					}
					
				}
				
				return true;
				
			}
			
			
			// destructor
			~ServerManager () {
				free_socket ();
			}
		
};