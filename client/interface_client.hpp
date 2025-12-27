/* 
  this will have the information for command line interface
*/

namespace interface {
  void header ();
  std::string get_server_address ();
  
  int get_server_port ();
  
  int option_input (std::string src, std::string dest); // like get file size - file transfer - quit
  
  std::string get_src_file_name ();
  
  std::string get_dest_file_name ();
  
  void filename_header ();
};

void interface::header () {
  std::cout << "\n\n\t ------- ENTER SERVER INFORMATION -------" << std::endl;
  
  
}

std::string interface::get_server_address () {
  std::string l_address = "";
  
  std::cout << "Address - ";
  std::cin >> l_address;
  getchar ();
  
  return l_address;
}


int interface::get_server_port () {
  int user_input = 0;
  
  std::cout << "Port - ";
  std::cin >> user_input;
  getchar ();
  
  if (user_input > 1000) {
    return user_input;
  } else {
    std::cout << "\t\t ! interface::get_server_port - port must be greater than 1000, setting it to 4000 (default)" << std::endl;
    user_input = 4000; // default port
  }
  
  return user_input;
}

int interface::option_input (std::string src, std::string dest) {
  std::cout << "\n\t ***** Enter your option ****" << std::endl;
  
  int user_input = 0;
  
  std::cout << "\t\t 1 -> File Transfer, src : " << src << ", dest : " << dest << std::endl;
  std::cout << "\t\t 2 -> Get File Size, src : " << src  << std::endl;
  std::cout << "\t\t 3 -> Quit Program" << std::endl;
  
  std::cin >> user_input;
  getchar ();
  
  if (user_input > 3) {
    std::cout << "\t\t\t ! interface::option_input - enter commands 1 - 3, set default - 2" << std::endl;
    user_input = 2; // default behavior - check for file size
  }
  
  if (user_input < 0) {
    std::cout << "\t\t\t ! interface::option_input - enter commands 1 - 3, set default - 2" << std::endl;
    user_input = 2;
  }
  
  return user_input;
}

void interface::filename_header () {
  std::cout << "\n\n\t ****** ENTER FILE NAMES  *******" << std::endl;
}

std::string interface::get_src_file_name () {
  std::string user_input = "";
  std::cout << "Source File (Server) : ";
  std::cin >> user_input;
  getchar ();
  
  
  return user_input;
}

std::string interface::get_dest_file_name () {
  std::string user_input = "";
  std::cout << "Destination File (Client) : ";
  std::cin >> user_input;
  getchar ();
  
  
  return user_input;
}

