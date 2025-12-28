/* 
  this will be the server for this program
  
  I'm going to use SDL, SDL_net
  
  -> this server can only pair with 1 client at a time 
*/
#define NO_OF_COMMANDS 3

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <fstream>

#include "./ServerManager.cpp"
#include "./PacketManager.cpp"

#include "./BundleManager_server.hpp"

#include "./Functions_server.hpp"

#include "./main_loop.hpp" // everything is here

#include "./Interface_server.hpp"


// function main
int main (int argc, char** argv) {
  // initializing libraries
  if (!func::init_library () ) {
    std::cout << "\t! Could not initialize library" << std::endl;
    return -1;
  } else {
    std::cout << "\t* Library Initialized " << std::endl;
  }
  
  
  // allocating memory for the bundle manager
  BundleManager_server* bun1 = new BundleManager_server;
  if (bun1 == nullptr) {
    std::cout << "\t ! Could not allocate memory to the bundle manager" << std::endl;
    return -1;
  } else {
    std::cout << "\t* Memory allocated -> bundle manager " << std::endl;
  }
  
  // allocating members of the bundle manager
  bun1 -> allocate_bundle_manager ();
  
  // starting networking
  // taking port input from the user
  bun1 -> server1 -> server_port = interface::port_input ();
  bun1 -> server1 -> socket_type = "server";
  // changing the socket type here
  bun1 -> server1 -> create_socket ();
  // creating packet
  bun1 -> packet1 -> create_packet (bun1 -> string_size);
  
  func::read_global_commands ("../global_commands.txt", bun1 -> commands, bun1 -> COMMAND_NO);
  
  // loop
  event_program (bun1);
  
  
  
  
  // deleting bundle manager
  delete bun1;
  
  // quiting
  func::quit_library ();
  
  
  
  return 0;
}