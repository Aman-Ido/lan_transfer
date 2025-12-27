/* 
this file will have the class for packet manager that will only handle things related to package. 

like sending, receiving, decoding, encoding, package address and so on
*/
class PacketManager {
	public:
		UDPpacket* l_packet = nullptr; // local packet
		size_t packet_len = 0; // size of the packet
		
		// methods
			// free packet
			void free_packet () {
				if (this -> l_packet != nullptr) {
					SDLNet_FreePacket (this -> l_packet);
					this -> l_packet = nullptr;
					packet_len = 0;
				}
			}
			// create packet
			bool create_packet (size_t i_pkt_size) {
				free_packet (); // if there is previously one, then free that packet to create this one
				
				if (i_pkt_size > 0) {
					this -> l_packet = SDLNet_AllocPacket (i_pkt_size);
					if (this -> l_packet == nullptr) {
						std::cerr << "SDLNet_AllocPacket : " << SDLNet_GetError () << std::endl;
						return false;
					} else {
						std::cout << "Memory allocated to the packet : " << this -> l_packet -> maxlen << std::endl;
					}
				} else {
					std::cerr << "Cannot the size to negative" << std::endl;
					return false;
				}
				
				
				return true;
				
				
			}
			
			// method to load the packet (encode)
			bool load_packet (void* i_value, IPaddress* i_address, size_t i_size) {
				// memset (this -> l_packet -> data, 0, this -> l_packet -> maxlen);
				memset (this -> l_packet -> data, 0, i_size);
				memcpy (this -> l_packet -> data, i_value, i_size);
				this -> l_packet -> len = i_size;
				
        
        if (i_address != nullptr) {
          
          this -> l_packet -> address = *i_address;
        }
        
				// if (i_address.host == 0 && i_address.port == 0) { // then this is a client
					// this -> l_packet -> address = 
				// } else {
					// this one is a server
					// this -> l_packet -> address = *i_address;
					// std::cout << "load_packet () : " << i_address -> host << ":" << i_address -> port << std::endl;
				// }
				return true;
			}
			
			// method to unload the packet (decode)
/* 			IPaddress* unload_packet (void* i_value) {
				// memset (i_value, 0, this -> l_packet -> maxlen);
				memcpy (i_value, this -> l_packet -> data, this -> l_packet -> maxlen);
				std::cout << "the size is " << this -> l_packet -> maxlen << std::endl;
				// *i_address = this -> l_packet -> address;
				
				// return true;
				return &this -> l_packet -> address;
			} */
			
			void unload_packet (void* i_value, size_t n) {
        memset (i_value, 0, n);
				// memcpy (i_value, this -> l_packet -> data, this -> l_packet -> len);
        memcpy (i_value, this -> l_packet -> data, this -> l_packet -> len);
				
			}
			
			void t_unload_packet (void* msg) {
				// memcpy (&msg, this -> l_packet -> data, this -> l_packet -> maxlen);
				// std::cout << "the size is : " << this -> l_packet -> maxlen << std::endl;
				// std::cout << *msg -> username << ": " << *msg -> message << std::endl;
				std::cout << "Placeholder" << std::endl;
			}
			
			// method to send the packet
			
			
			
			// destructor
			~PacketManager () {
				free_packet ();
			}
};