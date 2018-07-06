//
// Created by Erik A. Partridge on 6/25/18.
//

#ifndef LJUS_VIEW_H
#define LJUS_VIEW_H

#include "../../external/json.hpp"
#include "RenderingEngine.h"
#include <string>
#include <memory>
#include <files/Filesystem.h>

namespace Ljus {
    template <class T>
    class View {
    public:
        /**
         * Constructs a View instance with the default rendering engine (Inja).
         * @param data the JSON context for the rendering of the view
         * @param view the full or relative path to the readable view file.
         */
        View(T data, std::string view) {
            this->engine = nullptr;
            this->view = std::move(view);
            this->data = std::move(data);
        }

        /**
         * Constructs a View instance with a pointer to any given rendering engine.
         * @param engine the rendering engine to be used for templating.
         * @param data the JSON context for the rendering of the view
         * @param view the full or relative path to the readable view file.
         */
        View(std::shared_ptr<Ljus::RenderingEngine<T>> engine, T data, std::string view){
            this->engine = std::move(engine);
            this->view = std::move(view);
            this->data = std::move(data);
            this->result = std::string();
        }

        /**
         * Renders the view to an HTML string
         * @return the fully rendered HTML in string form. ** Not ** a path to an HTML file.
         */
        std::string render(){
            this->result = this->engine.get()->render( data, Filesystem::get(this->view));
            return this->result;
        }

    private:
        std::shared_ptr<Ljus::RenderingEngine<T>> engine;
        std::string view;
        T data;
        std::string result;
    };
};

#endif //LJUS_VIEW_H
