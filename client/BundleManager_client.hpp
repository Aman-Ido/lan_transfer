/* 
  this is the bundle manager for the client
  
  and this one is specific to a program individual 
*/

class BundleManager_client {
  public:
    // members
    ServerManager* server1;
    PacketManager* packet1;
    
    int string_size = 50; // default value
    char* string1; // for data transfer
    
    bool _quit_ = false; // main switch 
    
    int number_of_command = 3;
    std::string global_commands [3];
    
    bool _is_waiting_ = false;
    
    std::string responding_to = "";
    
    bool _close_thread_ = false;
    
    std::string file_name = ""; // source file name
    std::string dest_name = ""; // destination name
    
    // methods
    BundleManager_client ();
    
    ~BundleManager_client ();
    
    void free_bundle_manager ();
    
    void allocate_bundle_manager (); // allocates dynamic memory to the members
};

BundleManager_client::BundleManager_client () {
  this -> server1 = nullptr;
  this -> packet1 = nullptr;
  this -> string1 = nullptr;
}

BundleManager_client::~BundleManager_client () {
  free_bundle_manager ();
}

void BundleManager_client::free_bundle_manager () {
  if (this -> server1 != nullptr) {
    delete [] this -> server1;
    this -> server1 = nullptr;
  }
  
  if (this -> packet1 != nullptr) {
    delete [] this -> packet1;
    this -> packet1 = nullptr;
  }
  
  if (this -> string1 != nullptr) {
    delete [] this -> string1;
    this -> string1 = nullptr;
  }
}

void BundleManager_client::allocate_bundle_manager () {
  this -> server1 = new ServerManager [1]; // change this number for more
  if (this -> server1 == nullptr) {
    std::cout << "\t\t ! Could not allocate memory -> server1" << std::endl;
    return;
  }
  
  this -> packet1 = new PacketManager [1]; // change this number for more
  if (this -> packet1 == nullptr) {
    std::cout << "\t\t ! Could not allocate memory -> packet1" << std::endl;
    return;
  }
  
  this -> string1 = new char [this -> string_size]; // change this number for more
  if (this -> string1 == nullptr) {
    std::cout << "\t\t ! Could not allocate memory -> string1" << std::endl;
    return;
  }
}