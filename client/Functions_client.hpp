/* 
  this file will have all the functions for this program
*/
namespace func  {
  // init library - for initializing sdl and sdl net
  bool init_library ();
  
  // quit library - for quitting sdl and sdl net
  void quit_library ();
  
  // reallocates the string size and packet size
  bool reallocate_string (BundleManager_client* i_bun, size_t update_size);
  
  // read global commands
  void read_global_commands (std::string file_name, BundleManager_client* i_bun);
  
  // compare incoming messages
  /* 
    any incoming message is sent to this function and according to responding variable it will then to go a designated
    function
  */
  bool compare_incoming_messages (BundleManager_client* i_bun);
  
  namespace client {
    void transfer_file (BundleManager_client* i_bun);
    
    void receive_file_size (BundleManager_client* i_bun);
    
    
    void set_file_name (BundleManager_client* i_bun);
    
    namespace result {
      bool r_transfer_file (BundleManager_client* i_bun);
      
      bool r_file_size (BundleManager_client* i_bun);
      
      void r_file_name (BundleManager_client* i_bun);
    };
  };
};

bool func::init_library () {
  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL_Init () : " << SDL_GetError () << std::endl;
    return false;
  } else {
    std::cout << "SDL Initialized" << std::endl;
  }
  
  if (SDLNet_Init () < 0) {
    std::cout << "SDLNet_Init () : " << SDLNet_GetError () << std::endl;
    return false;
  } else {
    std::cout << "SDLNet Initialized" << std::endl;
  }
  
  return true;
}

void func::quit_library () {
  SDLNet_Quit ();
  SDL_Quit ();
}


// reallocates the string size
bool func::reallocate_string (BundleManager_client* i_bun, size_t update_size) {
  
  if (update_size < 1) {
    std::cout << "\t\t ! func::reallocate_string - update_size must be greater than 1" << std::endl;
    return false;
  } 
  
  // updating the system size
  i_bun -> string_size = update_size;
  
  
  // reallocating string
  if (i_bun -> string1 != nullptr) {
    delete [] i_bun -> string1;
    i_bun -> string1 = nullptr;
    
    i_bun -> string1 = new char [i_bun -> string_size];
    if (i_bun -> string1 == nullptr) {
      std::cout << "\t\t ! func::reallocate_string - could not reallocated - string1" << std::endl;
      return false;
    } else {
      std::cout << "\t\t * func::reallocate_string - reallocated - string1" << std::endl;
    }
    
  }
  
  // for the packet
  i_bun -> packet1 -> free_packet ();
  
  // reallocating
  if (!i_bun -> packet1 -> create_packet (i_bun -> string_size)) {
    std::cout << "\t\t ! func::reallocate_string::i_bun -> packet1 -> create_packet - error" << std::endl;
    return false;
  } else {
    std::cout << "\t\t * func::reallocate_string::i_bun -> packet1 -> create_packet - success" << std::endl;
  }
  
  return true;
  
}


void func::client::set_file_name (BundleManager_client* i_bun) {
  interface::filename_header (); // showing the header
  
  // getting hte inputs
  std::string src_file = "";
  std::string dest_file = "";
  
  src_file = interface::get_src_file_name (); // gets the source file name
  dest_file = interface::get_dest_file_name (); // gets the destination file name
  
  // updating the destination file name in the system
  i_bun -> file_name = src_file;
  i_bun -> dest_name = dest_file;
  
  std::cout << "*****************\n" << std::endl;
  std::cout << "Source File : " << i_bun -> file_name << std::endl;
  std::cout << "Destination File : " << i_bun -> dest_name << std::endl;
  std::cout << "*****************\n" << std::endl;
  
  // convert the information into char* 
  strcpy (i_bun -> string1, i_bun -> file_name.c_str());
  
  
  // load the file
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> server1 -> server_ip, i_bun -> string_size)) {
    std::cout << "\t\t ! func::client::set_file_name - could not load the packet" << std::endl;
    return;
  } else {
    std::cout << "\t\t * func::client::set_file_name - loaded the packet" << std::endl;
  }
  
  // sending the packet
  if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
    std::cout << "Information Sent : " << std::endl;
    std::cout << "\t\t m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
    
    i_bun -> _is_waiting_ = true;
    
    i_bun -> responding_to = i_bun -> global_commands[2]; // __file_name__
  }
  
}

void func::client::transfer_file (BundleManager_client* i_bun) {
  /* 
    it is assumed that you have already read the file size
    
    if not reading it is very important, it automatically updates the size of the packet and data char string 
    
    I was in a dilema if I want to call that function here or should I let the user call for it, 
    
    and I have decided on the latter
  */
  
  /* 
    updating the string
    
    for i_bun -> global_commands it is assumed that you have already called 
    func::get_global_commands function
  */
  std::string t_string = i_bun -> global_commands [0]; // __file_transfer__
  
  strcpy (i_bun -> string1, t_string.c_str());
  
  // loading the packet
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> server1 -> server_ip, i_bun -> string_size)) {
    std::cout << "\t\t ! func::client::transfer_file - Could not load Packet " << std::endl;
    return;
  } else {
    std::cout << "\t\t * func::client::transfer_file - Packet Loaded" << std::endl;
  }
  
  // sending the packet
  if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
    std::cout << "\t\t ! func::client::transfer_file - Message Sent" << std::endl;
    std::cout << "\t\t\t m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
    
    i_bun -> responding_to = i_bun -> global_commands [0]; // __file_transfer__
    i_bun -> _is_waiting_ = true;
  }
}

void func::client::receive_file_size (BundleManager_client* i_bun) {
  /*
    this function will only ask for the file size nothing more, it won't be doing anything with the received information
  */
  
  std::string t_string = i_bun -> global_commands[1]; // __file_size__
  
  strcpy (i_bun -> string1, t_string.c_str());
  
  // loading the packet
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> server1 -> server_ip, i_bun -> string_size)) {
    std::cout << "\t\t ! func::client::receive_file_size - Could not load the packet" << std::endl;
    return;
  } else {
    std::cout << "\t\t * func::client::receive_file_size - Packet Loaded" << std::endl;
  }
  
  // sending the packet
  if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
    std::cout << "\t\t * func::client::receive_file_size - Message Sent" << std::endl;
    std::cout << "\t\t\t m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
    
    i_bun -> _is_waiting_ = true;
    i_bun -> responding_to = i_bun -> global_commands[1]; // __file_size__
  }
}

bool func::client::result::r_transfer_file (BundleManager_client* i_bun ) {
  /* 
    when we get the information from the server for the file
  */
  std::string t_string = i_bun -> string1;
  
  /*
  	i_bun -> string1[i_bun -> string_size] = '\0';
  	this line makes it crash in linux system.
  */
  
  // opening the file with the dest-name
  std::fstream t_file;
  
  t_file.open (i_bun -> dest_name, std::ios::out | std::ios::binary);
    
    t_file.write (i_bun -> string1, i_bun -> string_size );
  
    // check if the file is written
    t_file.seekg (0, std::ios::end);
    
    std::streampos y = t_file.tellg();
    int file = static_cast <int> (y);
    
    if (file == 0) {
      std::cout << "\t\t ! func::client::result::r_transfer_file - could not write the file" << std::endl;
      i_bun -> _is_waiting_ = false;
      i_bun -> responding_to = "";
      return false;
    } else {
      std::cout << "\t\t * func::client::result::r_transfer_file - File written\n" << std::endl;
      std::cout << "\t\t\t ^ File - " << i_bun -> dest_name << std::endl;
      std::cout << "\t\t\t ^ Size - " << file << " bits" << std::endl;
    }
    
  t_file.close ();
  
  i_bun -> _is_waiting_ = false;
  i_bun -> responding_to = "";
  
  
  
  
  
  return true;
}

bool func::client::result::r_file_size (BundleManager_client* i_bun) {
  /* 
    it is assumed that the information is unloaded onto the i_bun -> string1;
  */
  
  // from char* to std::string
  std::string t_string = i_bun -> string1;
  int t_file_size = 0;
  
  // message
  std::cout << "Received Information - " << t_string << " bits " << std::endl;
  std::cout << "** Converting to Integer " << std::endl;
  
  t_file_size = std::stoi (t_string); // converted, std::string - integer
  if (t_file_size == 0) {
    std::cout << "\t\t ! func::client::result::r_file_size - Couldn't convert, std::string - integer" << std::endl;
    return false;
  } else {
    std::cout << "\t\t * func::client::result::r_file_size - Converted, std::string - integer" << std::endl;
  }
  
  // t_file_size += 1;// increment one bit
  
  // updating the sizes 
  if (!func::reallocate_string (i_bun, t_file_size))   {
    std::cout << "\t\t ! func::client::result::r_file_size - Could not reallocated - error" << std::endl;
    return false;
  } else {
    std::cout << "\t\t ! func::client::result::r_file_size - Reallocated - Success" << std::endl;
  }
  
  // after everything is success, we will again listen for 
  i_bun -> _is_waiting_ = false;
  i_bun -> responding_to = "";
  
  return true;
}

void func::client::result::r_file_name (BundleManager_client* i_bun) {
  /* 
    we just received the message saying we have received the message from the server
  */
  
  std::string t_string = i_bun -> string1;
  
  std::cout << "***** From Server - " << t_string << std::endl;
  
  
  i_bun -> _is_waiting_ = false;
  i_bun -> responding_to = "";
  
  
}


bool func::compare_incoming_messages (BundleManager_client* i_bun) {
  /* 
    it is listening for the commands
  */
  i_bun -> packet1 -> unload_packet (i_bun -> string1, i_bun -> string_size);
    
  // according to response
  if (i_bun -> responding_to == i_bun -> global_commands[0]) { // transfer
    if (!func::client::result::r_transfer_file (i_bun)) {
      std::cout << "\t\t ! func::compare_incoming_messages - transfer - fail" << std::endl;
      return false;
    } 
  } else if (i_bun -> responding_to == i_bun -> global_commands [1]) { // file size
    if (!func::client::result::r_file_size (i_bun)) {
      std::cout << "\t\t ! func::compare_incoming_messages - file size - fail" << std::endl;
      return false;
    } 
  } else if (i_bun -> responding_to == i_bun -> global_commands [2]) { // file name
    func::client::result::r_file_name (i_bun);
    // std::cout << "The value of the waiting  - " << i_bun -> _is_waiting_ << std::endl;
    // std::cout << "the value of the responding to - " << i_bun -> responding_to << std::endl;
  }
    
    
  
  return true;
}


void func::read_global_commands (std::string file_name, BundleManager_client* i_bun) {
  // reading the global commands
  
  
  // opening file
  std::fstream t_file;
  std::string t_string = "";
  
  int length = i_bun -> number_of_command;
  t_file.open (file_name, std::ios::in);
  
    // reading the file
    for (int i = 0; i < length; i++) {
      std::getline (t_file, t_string);
      i_bun -> global_commands[i] = t_string;
    }
  
  t_file.close ();
  
  
  // return true;
}
