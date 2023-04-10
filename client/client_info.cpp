#include "client_info.hpp"

namespace prop_tree = boost::property_tree;

client_info::client_info(const char *config_path) {
  prop_tree::ptree client_info_json;
  prop_tree::read_json(config_path, client_info_json);
  client_name = (char *)malloc(100);
  if (boost::optional<std::string> name =
          client_info_json.get_optional<std::string>("name")) {
    strcpy(client_name, name.get().c_str());
  } else {
    strcpy(client_name, "ClientName404");
  }
}

client_info::~client_info() { free(client_name); }

char *client_info::get_client_name() { return client_name; }
