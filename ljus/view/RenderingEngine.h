//
// Created by Erik A. Partridge on 6/25/18.
//

#ifndef LJUS_RENDERINGENGINE_H
#define LJUS_RENDERINGENGINE_H


#include "../../external/json.hpp"
#include <string>
namespace Ljus {
    class RenderingEngine {
    public:
        /**
         * Any class that is to be used as a rendering engine has to be able to render a file given JSON data to an HTML string.
         * @param data the JSON context for the rendering, this is how we pass variables
         * @param view the full or relative path to the view file
         * @return the html content as a string, not as a file
         */
        virtual std::string render(nlohmann::json data, std::string view)= 0;

    private:
        std::string view;
        nlohmann::json data;
    };

};

#endif //LJUS_RENDERINGENGINE_H
