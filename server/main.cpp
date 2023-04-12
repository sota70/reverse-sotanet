#include "command.hpp"
#include "ssl_server_socket.hpp"
#include <vector>

#define SERVER_PORT 3000
#define CERT_PATH "../cert.pem"
#define PRIVATE_KEY_PATH "../private_key.pem"
#define MAX_PAYLOAD_SIZE 1024

int main();

int main() {
  char received_payload[MAX_PAYLOAD_SIZE];
  char raw_command[MAX_PAYLOAD_SIZE];
  int client_socket;
  vector<string> cmd_args;
  command *command_struct;
  ssl_server_socket ssl_server_sock(SERVER_PORT, CERT_PATH, PRIVATE_KEY_PATH);
  SSL *ssl;
  if (!ssl_server_sock.listen_connection()) {
    return -1;
  }
  while (true) {
    client_socket =
        accept(ssl_server_sock.get_server_socket(), nullptr, nullptr);
    printf("normal connection established\n");
    ssl = SSL_new(ssl_server_sock.get_ssl_ctx());
    SSL_set_fd(ssl, client_socket);
    if (SSL_accept(ssl) != 1) {
      SSL_free(ssl);
      return -1;
    }
    printf("Connection established\n");
    while (true) {
      // resets previous command info because it might run previous command
      memset(received_payload, 0, MAX_PAYLOAD_SIZE);
      memset(raw_command, 0, MAX_PAYLOAD_SIZE);
      cmd_args.clear();
      printf("server >> $ ");
      cin.getline(raw_command, MAX_PAYLOAD_SIZE);
      command_struct = new command(raw_command, cmd_args);
      if (strcmp(command_struct->get_command_name(), "exit") == 0) {
        break;
      }
      SSL_write(ssl, command_struct->get_full_command(), MAX_PAYLOAD_SIZE);
      SSL_read(ssl, received_payload, MAX_PAYLOAD_SIZE);
      printf("%s\n", received_payload);
      delete command_struct;
    }
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client_socket);
  }
  return 0;
}
