//
// Created by Erik A. Partridge on 7/6/18.
//

#ifndef LJUS_MUSTACHEENGINE_H
#define LJUS_MUSTACHEENGINE_H

#include "RenderingEngine.h"
#include "../../external/mustache.hpp"
#include <string>

namespace Ljus {
    class MustacheEngine : public RenderingEngine<kainjow::mustache::data>{
        std::string render(kainjow::mustache::data data, std::string contents){
            kainjow::mustache::mustache tmpl(contents);
            std::stringstream ss;
            tmpl.render(data, [&ss](const std::string& str) {
                ss << str;
            });
            return ss.str();
        }
    };
}

#endif //LJUS_MUSTACHEENGINE_H
