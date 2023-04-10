#include "server_socket.hpp"
#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>

class ssl_server_socket {

public:
  ssl_server_socket(const char *server_address, int server_port,
                    const char *cert_path, const char *private_key_path);
  ~ssl_server_socket();
  bool listen_connection();
  int get_server_socket();
  SSL_CTX *get_ssl_ctx();

private:
  SSL_CTX *ssl_ctx;
  server_socket *server_sock;
};
