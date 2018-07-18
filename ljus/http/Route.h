//
// Created by erik on 09/09/17.
//

#ifndef LJUS_ROUTE_H
#define LJUS_ROUTE_H


#include <http/utils/Response.h>
#include <http/utils/Request.h>
#include <memory>
#include <regex>
#include <vector>

using namespace Ljus;

class Route {

public:
    static std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )>
    find( std::string method, std::string path );

    Route( std::string method, std::string path,
           std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action );

    static void add_route( std::string method, std::string path,
                           std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action );

    static void
    get( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action );

    static void
    put( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action );

    static void
    post( std::string path, std::function<Response( std::shared_ptr<Request>, std::shared_ptr<Response> )> action );

    static void register_routes();

    static void register_assets(std::string asset_path);

private:
    std::string method;
    std::regex path_regex;
    std::function<Response( std::shared_ptr<Request> request, std::shared_ptr<Response> response )> action;

    bool match( std::string method, std::string path );

};


#endif //LJUS_ROUTE_H
