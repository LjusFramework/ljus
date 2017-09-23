//
// Created by erik on 09/09/17.
//

#include <functional>
#include "Route.h"
#include "BaseController.h"

static std::vector<Route> routes;

std::function<Response( std::shared_ptr<Request> request, std::shared_ptr<Response> response )>

Route::find( std::string method, std::string path ) {
    for ( auto route : routes ) {
        if ( route.match(method, path)) {
            return route.action;
        }
    }
    throw 404;
}

Route::Route( std::string method, std::string path,
              std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action ) {
    this->method = std::move(method);
    this->path_regex = std::regex(path);
    this->action = action;
}

bool Route::match( std::string method, std::string path ) {
    if ( method == this->method ) {
        std::cmatch match;
        auto rmatch = std::regex_match(path, path_regex);
        return ( bool ) rmatch;
    } else {
        return false;
    }
}

void
Route::get( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action ) {
    Route::add_route("GET", std::move(path), action);
}

void
Route::post( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action ) {
    Route::add_route("POST", std::move(path), action);
}

void
Route::put( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action ) {
    Route::add_route("PUT", std::move(path), action);
}

void Route::add_route( std::string method, std::string path,
                       std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action ) {
    routes.push_back(Route(method, path, action));
}

void Route::register_routes() {
    Route::get("/", []( std::shared_ptr<Request> req, std::shared_ptr<Response> res ) -> Response {
        return BaseController().index(req, res);
    });
}

