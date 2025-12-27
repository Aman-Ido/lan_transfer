/* 
  this is the command center of the program
*/
#include <thread>
#define RECEIVE_DELAY 50

// function for SDLNet_UDP_Recv
void listen_client (BundleManager_client* i_bun) {
  // render here
  
  while (true) {
    
    if (SDLNet_UDP_Recv (i_bun -> server1 -> l_socket, i_bun -> packet1 -> l_packet) > 0) {
      // std::cout << "udp receiving" << std::endl;
      // i_bun -> packet1 -> unload_packet (i_bun -> string1, i_bun -> string_size);
      
      // std::string l_string = i_bun -> string1;
      func::compare_incoming_messages (i_bun);
      
    } // just shit
    
    
    if (i_bun -> _close_thread_) {
      break;
      return;
      
    }
    
    SDL_Delay (RECEIVE_DELAY);
  }
}

bool event_program (BundleManager_client* i_bun) {
  
  SDL_Event e;
  
  std::thread l_recv_thread (listen_client, i_bun);
  
  while (!i_bun -> _quit_) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        i_bun -> _quit_ = true;
      }
    }

    // else {
      // if (!func::compare_incoming_messages (i_bun)) {
        // return false;
        // i_bun -> _quit_ = true;
      // }
    // }
    int user_input = interface::option_input (i_bun -> file_name, i_bun -> dest_name);
    
    if (user_input == 1) {
      func::client::transfer_file (i_bun);
    } else if (user_input == 2) {
      func::client::receive_file_size (i_bun);
    } else {
      // send quit message to the server
      // changing the string
      strcpy (i_bun -> string1, "_quit_");
      
      // loading the string
      if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> server1 -> server_ip, i_bun -> string_size)) {
        std::cout << "\t\t ! Could not load packet _quit_" << std::endl;
        i_bun -> _quit_ = true;
        i_bun -> _close_thread_ = true;
        return false;
      } else {
        std::cout << "\t\t * Packet Loaded - _quit_" << std::endl;
      }
      
      // sending the packet
      if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
        std::cout << "Message Sent\n\t\t m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
      }
      
      i_bun -> _quit_ = true;
      i_bun -> _close_thread_ = true;
    }
  } 
    
  
  
  
  if (l_recv_thread.joinable()) {
    
    l_recv_thread.join ();
  }
  
  return true;
  
}