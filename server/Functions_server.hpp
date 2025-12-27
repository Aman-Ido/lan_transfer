/* 
  this file will only have functions
*/
namespace func {
  // declarations
  // init library - sdl, sdl net
  bool init_library ();
  
  // quit library - sdl, sdlnet
  void quit_library ();
  
  // function reallocate packet and lstring size
  bool reallocate_string (BundleManager_server* i_bun, size_t update_size);
  
  // reads the file and then get the string to the array
  bool read_global_commands (std::string file_name, std::string* commands, int size);
  
  // command to input value and compare it with others
  bool compare_incoming_values (BundleManager_server* i_bun, std::string i_value);
  
  int get_file_size (BundleManager_server* i_bun, std::string i_file_name);
  
  namespace server {
    /* 
      these are the functions related to the server 
      like return_file_size
      like setup_file_name
      like transfer_file
    */
    
    void return_file_size (BundleManager_server* i_bun); // loads and returns - sends the file size
    void setup_file_name (BundleManager_server* i_bun, std::string i_value); // sets the i_bun -> file_name from the packet -> data
    void transfer_file (BundleManager_server* i_bun); // loads the file content and sends it to the client
  };
};

int func::get_file_size (BundleManager_server* i_bun, std::string i_file_name) {
  
  std::fstream t_file; // declaring t_file
  
  t_file.open (i_file_name, std::ios::in | std::ios::binary); // opening the file
  
    t_file.seekg (0, std::ios::end); // putting the cursor to the end
    
    std::streampos y = t_file.tellg (); // getting the cursor position - size
    
    int size = static_cast <int> (y); // converting from std::streampos - int
  
  t_file.close (); // closing file
  
  
  return size;
}



bool func::reallocate_string (BundleManager_server* i_bun, size_t update_size) {
  if (update_size < 1) {
    std::cout << "\t\t ! func::reallocate_string - update_size must be greater than 1"  << std::endl;
    return false;
  }
  
  i_bun -> string_size = update_size;
  
  if (i_bun -> packet1 -> l_packet != nullptr) {
    i_bun -> packet1 -> free_packet ();
    
    // again allocating
    if (!i_bun -> packet1 -> create_packet (i_bun -> string_size)) {
      std::cout << "\t\t ! func::reallocate_string - create_packet - error" << std::endl;
      return false;
    }
    
  }
  
  if (i_bun -> string1 != nullptr) {
    delete [] i_bun -> string1;
    
    // reallocating
    i_bun -> string1 = new char [i_bun -> string_size];
    if (i_bun -> string1 == nullptr) {
      std::cout << "\t\t ! func::reallocate_string - reallocate string - error" << std::endl;
      return false;
    }
  }
  
  return true;
}

bool func::init_library () {
  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    std::cout << "sdl_init () : " << SDL_GetError () << std::endl;
    return false;
  } else {
    std::cout << "SDL Initialized " << std::endl;
  }
  
  
  if (SDLNet_Init () < 0) {
    std::cout << "sdlnet_init () : " << SDLNet_GetError () << std::endl;
    return false;
  } else {
    std::cout << "SDLNet Initialized " << std::endl;
  }
  
  
  return true;
}


void func::quit_library () {
  SDLNet_Quit ();
  SDL_Quit ();
}

/* 
  this will read the file and then fill the string array
*/
bool func::read_global_commands (std::string file_name, std::string* commands, int size) {
  std::string t_string = "";
  std::fstream t_file; // temporary file
  t_file.open (file_name, std::ios::in);
  
  
  for (int i = 0; i < size; i++) {
    std::getline (t_file, t_string);
    
    // commands[i] = t_string;
    commands[i] = t_string;
  }
  
  t_file.close ();
  
  return true;
}

/*
  this will compare the commands with the input value and calls the appropriate function
  it assumes that you have already called and unloaded the packet to l_string or the inputted string
 */
bool func::compare_incoming_values (BundleManager_server* i_bun, std::string i_value) {
  /* 
    file transfer
  */
  if (i_value == i_bun -> commands[0]) {
    // calling the func::server function
    func::server::transfer_file (i_bun);
  }
  
  /* 
    file size
  */
  else if (i_value == i_bun -> commands[1]) {
    func::server::return_file_size (i_bun);
  }
  
  else if (i_value == "_quit_") { /* if we receive _quit_ message from the client we quit server as well*/
    std::cout << "i: _quit_ message called" << std::endl;
    i_bun -> _quit_ = true;
    return false;
  }
  /* 
    file name
  */
  else {
    func::server::setup_file_name (i_bun, i_value);
  }
  
  
  
  return true;
}


/* 
  server functions
*/

void func::server::transfer_file (BundleManager_server* i_bun) {
  // opening file
  // reading the contents of the file
  int t_file_size = func::get_file_size (i_bun, i_bun -> file_name); // again checking if the file size is updated or not
  // if not we will update it here again
  
  
  // after updating all of these
  // if (i_bun -> string_size != t_file_size || i_bun -> string_size < t_file_size) {
    // std::cout << "\t\t ! If size if updated, you should not see this" << std::endl;
    // i_bun -> string_size = t_file_size;
    
    // func::reallocate_string (i_bun, t_file_size);
  // }
  
  
  // opening the file
  std::fstream t_file;
  t_file.open (i_bun -> file_name, std::ios::in);
    
    t_file.read (i_bun -> string1, i_bun -> string_size);
  
  t_file.close ();
  
  // convert the string to char*
  i_bun -> string1[i_bun -> string_size] = '\0';
  
  // loading the apcket
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> client_ip, i_bun -> string_size)) {
    std::cout << "\t\t ! func::server::transfer_file - Could not load packet (file) " << std::endl;
    return;
  } else {
    std::cout << "\t\t * func::server::transfer_file - Packed Loaded (file)" << std::endl;
  }
  
  // slight delay
  // SDL_Delay (i_bun -> SERVER_REFRESH_RATE);
  
  
  // SENDING THE PACKET
  if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
    std::cout << "\t\t * func::server::transfer_file - File Sent\n\t^ File - " << i_bun -> file_name << 
    "\n\t^ File Content - " << (char*) i_bun -> packet1 -> l_packet -> data << "\n\t^ File Size - " << i_bun -> string_size << " bits" << std::endl;
  }
}

void func::server::setup_file_name (BundleManager_server* i_bun, std::string i_value) {
  
  i_bun -> file_name = i_value; // set the name
  
  if (i_bun -> file_name == i_value) {
    std::cout << "Filename Recorded, m - " << i_bun -> file_name << std::endl;
  }
  
  // writing a message
  strcpy (i_bun -> string1, "@server.server@ - file recorded");
  
  // loading the message
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> client_ip, i_bun -> string_size)) {
    std::cout << "\t\t ! func::server::setup_file_name - load_packet - error" << std::endl;
    return;
  } else {
    std::cout << "\t\t * func::server::setup_file_name - load_packet - success" << std::endl;
  }
  
  // a slight delay before sending the message
  // SDL_Delay (i_bun -> SERVER_REFRESH_RATE);
  
  // sending the message
  if (SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet) > 0) {
    std::cout << "\t\t * Message Sent\n m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
  }
}

void func::server::return_file_size (BundleManager_server* i_bun) {
  // getting the file size
  int l_file_size = func::get_file_size (i_bun, i_bun -> file_name) + 1; // for '0'
  
  // convering integer to std::string
  std::string a = std::to_string (l_file_size);
  std::cout << "Converted String a - " << a << std::endl;
  
  // setting up the message
  strcpy (i_bun -> string1, a.c_str());
  
  
  // loading the message
  if (!i_bun -> packet1 -> load_packet (i_bun -> string1, &i_bun -> client_ip, i_bun -> string_size)) { // string_size - 50
    std::cout << "\t\t ! func::server::return_file_size - Could not load packet " << std::endl;
    return;
  }
  
  // slight delay before sending
  // SDL_Delay (i_bun -> SERVER_REFRESH_RATE);
  
  // sending the packet
  if( SDLNet_UDP_Send (i_bun -> server1 -> l_socket, -1, i_bun -> packet1 -> l_packet ) > 0) {
    std::cout << "\t\t - func::server::return_file_size - Message is sent, m - " << (char*) i_bun -> packet1 -> l_packet -> data << std::endl;
  }
  
  // l_file_size += 1; // incrementing by 1 bit
  // updating the new size
  if (func::reallocate_string (i_bun, l_file_size)) { // string_size = file.size
    std::cout << "\t\t * Packet, String reallocated, size - " << i_bun -> string_size << std::endl;
  } else {
    std::cout << "\t\t * Packet, string could not reallocate" << std::endl;
    return;
  }
  
  
  
}

