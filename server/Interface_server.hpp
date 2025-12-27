/* 
  for the command line interface
*/

namespace interface {
  int port_input ();
  void incoming (std::string i_message);
};

int interface::port_input () {
  int l_port;
  
  std::cout << "\t\t --- PORT INPUT ----" << std::endl;
  std::cout << "Enter Port Value : ";
  std::cin >> l_port;
  getchar (); // cancelling out '\n'
  
  if (l_port < 1000) {
    std::cout << "\t - The port value must be greater than '1000'" << std::endl;
    l_port = 4000; // default value
  }
  
  
  return l_port;
}


// just outputs the inputted text in a format
void interface::incoming (std::string i_message) {
  std::cout << "\t\t *** Incoming Message ***" << std::endl;
  std::cout << "\t\t m - " << i_message << std::endl;
}