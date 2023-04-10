#include "command_executor.hpp"

command_executor::command_executor(string &result_buffer)
    : result(result_buffer) {}

void command_executor::execute(const char *command) {
  char buffer[this->max_result_per_line];
  FILE *fp = popen(command, "r");
  while (fgets(buffer, this->max_result_per_line, fp) != NULL) {
    this->result.append(buffer);
  }
  pclose(fp);
}

string &command_executor::get_result() { return this->result; }
