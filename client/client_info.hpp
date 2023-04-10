#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

class client_info {

public:
  client_info(const char *config_path);
  ~client_info();
  char *get_client_name();

private:
  char *client_name;
};
