#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

class server_socket {

public:
  server_socket(int server_port);
  ~server_socket();
  bool listen_connection();
  int get_socket();

private:
  int sock;
  struct sockaddr_in header;
};
