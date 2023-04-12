#include "server_socket.hpp"

server_socket::server_socket(int server_port) {
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    sock = -1;
    return;
  }
  memset(&header, 0, sizeof(header));
  header.sin_family = AF_INET;
  header.sin_addr.s_addr = htons(INADDR_ANY);
  header.sin_port = htons(server_port);
  if (bind(sock, (struct sockaddr *)&header, sizeof(header)) < 0) {
    sock = -1;
    return;
  }
}

server_socket::~server_socket() {
  if (sock < 0) {
    return;
  }
  close(sock);
}

bool server_socket::listen_connection() {
  if (sock < 0) {
    return false;
  }
  if (listen(sock, SOMAXCONN) < 0) {
    return false;
  }
  return true;
}

int server_socket::get_socket() { return sock; }
