//
// Created by cents on 24/08/17.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "json.hpp"
#include "ljus/files/Filesystem.h"

using json = nlohmann::json;

const auto config = R"(
  {
    "app_key": "PLEASESETMETOSOMETHINGSECURERTHISNEEDSTOBE32CHARSORLONGERthisisBase64"
  }
)"_json;

namespace conf {
    const auto file_driver = Ljus::Filesystem();

}

#endif //CONFIG_H
