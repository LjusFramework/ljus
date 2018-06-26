//
// Created by Erik A. Partridge on 6/25/18.
//

#ifndef LJUS_VIEW_H
#define LJUS_VIEW_H

#include "../../external/inja.hpp"
#include "../../external/json.hpp"
#include "RenderingEngine.h"
#include "InjaEngine.cpp"
#include <string>
#include <memory>

namespace Ljus {

    class View {
    public:
        View(nlohmann::json data, std::string view);

        View(std::shared_ptr<Ljus::RenderingEngine> engine, nlohmann::json data, std::string view);

        std::string render();

    private:
        std::shared_ptr<Ljus::RenderingEngine> engine;
        std::string view;
        nlohmann::json data;
        std::string result;
    };
};

#endif //LJUS_VIEW_H
