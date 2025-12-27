/* 
  this will be server / client specific // evverything that I need from this program
*/
class BundleManager_server {
  public:
    ServerManager* server1;
    PacketManager* packet1;
    
    char* string1; // this string will only be used to transfer data 
    int string_size = 50; // default value - this is also the packet size
    
    std::string file_name; // to store the file name
    
    bool _quit_; // main switch
    
    IPaddress client_ip = {0}; // only one client
    
    const int SERVER_REFRESH_RATE = 0; // 50 miliseconds - it is just delay now
    
    const int COMMAND_NO = 3;
    std::string commands [3];
    
    // methods
    BundleManager_server ();
    
    ~BundleManager_server ();
    
    void free_bundle_manager ();
    
    void allocate_bundle_manager ();
    
};

// methods definition
BundleManager_server::BundleManager_server () {
  this -> server1 = nullptr;
  this -> packet1 = nullptr;
  this -> string1 = nullptr;
  
  this -> file_name = "";
  this -> _quit_ = false;
}

BundleManager_server::~BundleManager_server () {
  free_bundle_manager ();
}

void BundleManager_server::free_bundle_manager () {
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

void BundleManager_server::allocate_bundle_manager () {
  this -> server1 = new ServerManager [1]; // we can change the number of things here
  if (this -> server1 == nullptr) {
    std::cout << "\t * Could not allocate memory -> server1" << std::endl;
    return;
  }
  
  this -> packet1 = new PacketManager [1]; // we can change the number of things here
  if (this -> packet1 == nullptr) {
    std::cout << "\t * Could not allocate memory -> packet1" << std::endl;
    return;
  }
  
  this -> string1 = new char [this -> string_size]; // we can change the number of things here
  if (this -> string1 == nullptr) {
    std::cout << "\t * Could not allocate memory -> string1" << std::endl;
    return;
  }
}
