//
// Created by Erik A. Partridge on 6/25/18.
//

#ifndef LJUS_INJAENGINE_H
#define LJUS_INJAENGINE_H

#include "../../external/json.hpp"
#include "../../external/inja.hpp"
#include "RenderingEngine.h"
#include <string>
#include "../files/Filesystem.h"

namespace Ljus {

    class InjaEngine : public Ljus::RenderingEngine {
    public:
        std::string render(nlohmann::json data, std::string view) {
            inja::Environment env = inja::Environment();
            std::string result = env.render(Filesystem::get(view), data);
            return result;
        }
    };

};


#endif //LJUS_INJAENGINE_H
