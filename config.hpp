//
// Created by cents on 24/08/17.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "json.hpp"

using json = nlohmann::json;

const auto config = R"(
  {
    "app_key": "--SET ME TO SOMETHING SECURER THIS NEEDS TO BE 32 CHARS OR LONGER--"
  }
)"_json;

#endif //CONFIG_H
