#include "ssl_server_socket.hpp"

ssl_server_socket::ssl_server_socket(const char *server_address,
                                     int server_port, const char *cert_path,
                                     const char *private_key_path) {
  SSL_library_init();
  ssl_ctx = SSL_CTX_new(TLSv1_2_server_method());
  if (ssl_ctx == nullptr) {
    return;
  }
  SSL_CTX_set_ecdh_auto(ssl_ctx, 1);
  SSL_CTX_use_certificate_file(ssl_ctx, cert_path, SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(ssl_ctx, private_key_path, SSL_FILETYPE_PEM);
  server_sock = new server_socket(server_address, server_port);
}

ssl_server_socket::~ssl_server_socket() {
  SSL_CTX_free(ssl_ctx);
  delete server_sock;
}

bool ssl_server_socket::listen_connection() {
  return server_sock->listen_connection();
}

int ssl_server_socket::get_server_socket() { return server_sock->get_socket(); }

SSL_CTX *ssl_server_socket::get_ssl_ctx() { return ssl_ctx; }
