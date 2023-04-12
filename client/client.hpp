#pragma once

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class telnet_client {

public:
  telnet_client();
  telnet_client(const char *target_address, int port);
  bool connect_to_target();
  int get_client_socket();
  int get_header_size();
  struct sockaddr_in get_socket_header();
  void close_connection();

private:
  int client_socket;
  int header_size;
  struct sockaddr_in socket_header;
};
