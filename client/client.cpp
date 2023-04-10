#include "client.hpp"

telnet_client::telnet_client() = default;

telnet_client::telnet_client(const char *target_address, int port) {
  int sock;
  struct sockaddr_in header;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    this->client_socket = -1;
    this->header_size = -1;
    this->socket_header = nullptr;
    return;
  }
  memset(&header, 0, sizeof(header));
  header.sin_family = AF_INET;
  header.sin_addr.s_addr = inet_addr(target_address);
  header.sin_port = htons(port);
  this->client_socket = sock;
  this->header_size = sizeof(header);
  this->socket_header = &header;
}

bool telnet_client::connect_to_target() {
  if (this->client_socket < 0) {
    return false;
  }
  if (connect(this->client_socket, (struct sockaddr *)this->socket_header,
              this->header_size) < 0) {
    return false;
  }
  return true;
}

int telnet_client::get_client_socket() { return this->client_socket; }

int telnet_client::get_header_size() { return this->header_size; }

struct sockaddr_in *telnet_client::get_socket_header() {
  return this->socket_header;
}

void telnet_client::close_connection() {
  if (this->client_socket < 0) {
    return;
  }
  close(this->client_socket);
}
