#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class command {

public:
  command(const char *cmd, vector<string> &_args);
  const char *get_command_name();
  const char *get_full_command();
  vector<string> &get_arguments();

private:
  string command_name;
  string full_command;
  vector<string> &args;
};
