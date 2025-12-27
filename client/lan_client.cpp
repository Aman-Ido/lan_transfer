/* 
  this is the client part of that program
  
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <string>
#include <fstream>

#include "./ServerManager.cpp"
#include "./PacketManager.cpp"

#include "./interface_client.hpp"

#include "./BundleManager_client.hpp"
#include "./Functions_client.hpp"
#include "./main_loop.hpp"

// function main 
int main (int argc, char** argv) {
  if (!func::init_library ()) {
    std::cout << "! Could not init library" << std::endl;
    return -1;
  } else {
    std::cout << "* Library Initialized" << std::endl;
  }
  
  
  // allocating memory for bundle manager
  BundleManager_client* bun1 = new BundleManager_client[1];
  if (bun1 == nullptr) {
    std::cout << "! Could not allocate memory - bun1 " << std::endl;
    return -1;
  } else {
    std::cout << "*Memory allocatd - bun1" << std::endl;
  }
  
  // allocating members of the bundle manager
  bun1 -> allocate_bundle_manager ();
  
  // taking inputs from the user
  interface::header ();
  std::string server_address = interface::get_server_address ();
  int server_port = interface::get_server_port ();
  
  bun1 -> server1 -> server_address = server_address;
  bun1 -> server1 -> server_port = server_port;
  bun1 -> server1 -> socket_type = "client";
  
  // reading the global commands
  func::read_global_commands ("../global_commands.txt", bun1);
  if (bun1 -> global_commands[0] == "__file_transfer__") {
    std::cout << "Global Commands is read\n\n\n" << std::endl;
  }
  
  // initializing - server and packet
  if (!bun1 -> server1 -> create_socket ()) {
    std::cout << "! create socket - error" << std::endl;
    return -1;
  }
  
  if (!bun1 -> packet1 -> create_packet (bun1 -> string_size)) {
    std::cout << "! create packet - error" << std::endl;
    return -1;
  }
  
  
  
  // calling in for file names
  func::client::set_file_name (bun1);
  
  
  
  
  if (!event_program (bun1)) {
    return -1;
  }
  
  
  delete [] bun1;
  
  func::quit_library ();
  
  return 0;
}