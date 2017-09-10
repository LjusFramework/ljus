//
// Created by erik on 09/09/17.
//

#ifndef LJUS_ROUTE_H
#define LJUS_ROUTE_H


#include <http/utils/Response.h>
#include <http/utils/Request.h>
#include <memory>

class Route {

public:
    static std::function<Response( std::shared_ptr<Request> request, std::shared_ptr<Response> response )>
    find( std::string method, std::string path );
};


#endif //LJUS_ROUTE_H
