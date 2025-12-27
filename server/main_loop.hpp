/* 
  everything is here it's like the main control base
*/

// #include "TimeManagement.hpp"

// break time
#define BREAK_TIME 6 // seconds

bool event_program (BundleManager_server* i_bun);

bool event_program (BundleManager_server* i_bun) {
  
  SDL_Event e;
  
  bool recorded = false;
  
  
  while (!i_bun -> _quit_) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        i_bun -> _quit_ = true;
      }
    }
    // read here
    
    // listen for incoming messages
    if (SDLNet_UDP_Recv (i_bun -> server1 -> l_socket, i_bun -> packet1 -> l_packet) > 0) {
      /*
        the functions after these have assumed that the incoming packet data is already stored /
        unloaded into the i_bun -> string1
        and put into a local std::string
      */
      
      if (!recorded) {
        i_bun -> client_ip = i_bun -> packet1 -> l_packet -> address;
        recorded = true;
      }
      
      // loading the data
      i_bun -> packet1 -> unload_packet (i_bun -> string1, i_bun -> string_size);
      
      std::string local_string = i_bun -> string1;
      
      // calling for the functions - compare and call for the necessary function automatically
      func::compare_incoming_values (i_bun, local_string);
      
      // timer::stop_timer ();
      
      
      
    }
    
    // checking
    
    
    
    
  }
  
  
  
  return true;
}