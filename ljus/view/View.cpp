//
// Created by Erik A. Partridge on 6/25/18.
//

#include "View.h"
#include <utility>
#include <memory>

Ljus::View::View(nlohmann::json data, std::string view) {
    this->engine = nullptr;
    this->view = std::move(view);
    this->data = std::move(data);
}

Ljus::View::View(std::shared_ptr<Ljus::RenderingEngine> engine,nlohmann::json data, std::string view) {
    this->engine = std::move(engine);
    this->view = std::move(view);
    this->data = std::move(data);
    this->result = std::string();
}

std::string Ljus::View::render() {
    this->result = this->engine.get()->render( data, view);
    return this->result;
}

