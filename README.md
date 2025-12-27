# Lan Transfer - Program
This program is specific to LAN ***(Local Area Network)***. It does not need to compile any .dll files (except the ones that you already need like, SDL's dll file) or anything. It is just header files and a single main file ***(For Server - /lan_transfer/server/lan_server.cpp)*** and ***(For client - /lan_transfer/client/lan_client.cpp)***. You compile those files and you get executable.

# How to Compile?
Compilation is platform specific. However, in Linux systems please make sure to have permission. 

### Necessary Libraries
    1. C/C++
    2. SDL2
    3. SDL2_net
_In future, this program may get ported in SDL3_

### In Windows
For Client
```
g++ lan_client.cpp -o lan_client -I/include/directory/ -L/library/directory/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_net
```

For Server
```
g++ lan_server.cpp -o lan_server -I/include/directory/ -L/library/directory/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_net
```

_If you are confused as to how to link SDL libraries, check this video
[
Simple SDL2 Setup in directory (MinGW, VS Code, Windows)](https://www.youtube.com/watch?v=H08t6gD1Y1E) from [HerbGlitch](https://www.youtube.com/@herbglitch)_

### In Linux
For Client
```
g++ lan_client.cpp -o lan_client -pthread -lSDL2 -lSDL2_net
```

For Server
```
g++ lan_server.cpp -o lan_server -lSDL2 -lSDL2_net
```

# More About the Program
The Process goes something like this:
```
# Server
- Opens port with User Inputted value (Must be greater than 1000).
- Starts Listening for Client Packet
- When server receives file_name (adds the packet's address to the local IPaddress variable), we save that file_name to the a variable and 
sends file_name recorded message to the client.
- When asked for file_size : Server opens the file (from saved file_name) and returns its size (if there is any, there are plenty of bugs if the file is 
not there.)
- When asked for transfer_file: Server opens the file (from saved file_name) and
gets all the information from that file to a string and sends it to the client
(Thus, if the file is really really, large it is a problem. However, there maybe updates in the future)
- When Client Quits- _quit_ message is sent to the server. And the server will exit itself.
```

```
# Client
- Opens Socket with user Inputted <server_address> and <server_port> value.
- Loads and Sends desired file name (with location - like C:/users/user/Desktop/
files/file1.txt) It is suggested that you create a folder like /media/ inside 
of the /server/ folder. Also Remember, your input is raw feeded to the 
std::fstream (user_inputted_file_name, std::ios::in)
- The client does not wait for the response from the Server to ask for inputs. (Multi-Thread)
- 2, 1, 3 / file_size, file_transfer, quit.
- Client Must ask for file size (the default size is 50). Asking for size automatically updates the default buffer and packet size with the
returned value from the Server.
- Responding to file transfer :- Client will open a file stream with destination
file name. And write to it with the server's response. 
- Finally exiting will exit the program safely. Exiting in client will exit in server as well.
```

### Limitations
```
1. Large files cannot be sent as of now. It's not like it can't be sent. It's just that 
it will take forever. Also, there is only one buffer. 
2. If the transfer takes more time, there is no way to know it, because the program will just freeze or wait for input. 
3. It is limited to LAN (no exactly, if you create a server on a computer and let your router 
do port-forwarding, then people can access your computer files with your WAN IP
and port, much like in games like Counter Strike. e.g. 2.xx.xxxx.x.x.x:23154)
```

### Future Plans
```
1. I would like to create just TUI in the future with this. Maybe I will, you know like 
I type 
lan_client -Sa 192.168.1.xx -Sp 4000 -fn /Desktop/file1/index.html -dn /Desktop/file2/dest_index.html 

2. I would also like to send packets partially, 🤔 how do I put this.
like I only copy 200 bytes of data from server and send it to the client at a time.
Keep sending 200 bytes of data to the client. 
In case the information flow is cut out then we will again resume from where we left off.

3. If possible I would also like to have a GUI. In future that is with loading bar.
```

Thank you all for reading my yapping. 

# Also Just So You Want to Know
1. Functions - file holds all the functions
2. BundleManager - has all the things that are needed
3. main_loop - file has the main program loop
4. interface - file has that tui interface
5. main_file (lan_client.cpp / lan_server.cpp) - file only calls the functions
6. The global_commands file has - few commands like (transfer, file_size, file_name) and even changing commands won't make much of a difference. I guess

# Demo Images / Videos
The images / videos will be available soon. [Youtube](https://youtube.com)

# Why Create Such an 'Abomination'?
Well truth to be told, I was bored with my jobless life. I just had to do something so I chose to create this. I have a old pc with linux on it. And sometimes (only sometimes) open that computer to check compatibility of the program that I created, but while doing that, I have to transfer the original files from my Windows computer to my Linux computer. There are programs such as [Samba](https://www.samba.org/). But due to some complications I was unable to setup Samba. Thus, I planned on creating this 'Abomination'.


_Also this README.md file was edited in [markdownlivepreview.com](https://markdownlivepreview.com)_