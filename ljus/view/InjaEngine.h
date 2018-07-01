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
        /**
         * This renders a view with passed JSON data as the context, using Inja.
         * @param data the JSON context which should be used to render the view. Any of the included variables in data can be used in the inja template
         * @param view the path, relative or full, to the view. Must be readable by the user running the program.
         * @return a string containing the fully rendered HTML / MD result
         */
        std::string render(nlohmann::json data, std::string view) {
            inja::Environment env = inja::Environment();
            std::string result = env.render(Filesystem::get(view), data);
            return result;
        }
    };

};


#endif //LJUS_INJAENGINE_H
