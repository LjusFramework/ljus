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
        /**
         * Constructs a View instance with the default rendering engine (Inja).
         * @param data the JSON context for the rendering of the view
         * @param view the full or relative path to the readable view file.
         */
        View(nlohmann::json data, std::string view);

        /**
         * Constructs a View instance with a pointer to any given rendering engine.
         * @param engine the rendering engine to be used for templating.
         * @param data the JSON context for the rendering of the view
         * @param view the full or relative path to the readable view file.
         */
        View(std::shared_ptr<Ljus::RenderingEngine> engine, nlohmann::json data, std::string view);

        /**
         * Renders the view to an HTML string
         * @return the fully rendered HTML in string form. ** Not ** a path to an HTML file.
         */
        std::string render();

    private:
        std::shared_ptr<Ljus::RenderingEngine> engine;
        std::string view;
        nlohmann::json data;
        std::string result;
    };
};

#endif //LJUS_VIEW_H
