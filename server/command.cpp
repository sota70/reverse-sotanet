#include "command.hpp"

void split(char *text, const char *delimiter, vector<string> &out) {
  char *token = strtok(text, delimiter);
  while (token != NULL) {
    out.push_back(token);
    token = strtok(NULL, delimiter);
  }
}

command::command(const char *cmd, vector<string> &_args) : args(_args) {
  this->full_command.append(cmd);
  split((char *)cmd, " ", this->args);
  this->command_name.append(this->args.at(0).c_str());
  this->args.erase(this->args.begin());
}

const char *command::get_command_name() { return this->command_name.c_str(); }

const char *command::get_full_command() { return this->full_command.c_str(); }

vector<string> &command::get_arguments() { return this->args; }
