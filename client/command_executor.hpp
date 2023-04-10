#pragma once

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

class command_executor {

public:
  command_executor(string &result_buffer);
  void execute(const char *command);
  string &get_result();

private:
  string &result;
  int max_result_per_line = 100;
};
