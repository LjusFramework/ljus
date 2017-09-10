#include "ljus.h"
#include "external/server/server_http.hpp"
#include "external/json/src/json.hpp"
#include "http/Route.h"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {

    HttpServer server;
    server.config.port = 8000;
    server.config.address = "127.0.0.1";

    //Pass to routes function
    try {
        server.resource["^/*"]["POST"] = []( shared_ptr<HttpServer::Response> response,
                                             shared_ptr<HttpServer::Request> request ) {
            if ( request.get()->path.size() > 5000 ) {
                throw "URL too long";
            }
            auto content = request->content.string();
            auto rq = make_shared<Request>(new Request);
            auto res = make_shared<Response>(new Response);
            std::function<Response( std::shared_ptr<Request> request,
                                    std::shared_ptr<Response> response )> action = Route::find(request.get()->method,
                                                                                               request.get()->path);
            auto route_response = action(rq, res);
            response->write(res.get()->generate(), res.get()->get_headers());
        };
        server.resource["^/*"]["GET"] = []( shared_ptr<HttpServer::Response> response,
                                            shared_ptr<HttpServer::Request> request ) {
            if ( request.get()->path.size() > 5000 ) {
                throw "URL too long";
            }
            auto rq = make_shared<Request>(new Request);
            auto res = make_shared<Response>(new Response);
            std::function<Response( std::shared_ptr<Request> request,
                                    std::shared_ptr<Response> response )> action = Route::find(request.get()->method,
                                                                                               request.get()->path);
            auto route_response = action(rq, res);
        };
        server.resource["^/*"]["PATCH"] = []( shared_ptr<HttpServer::Response> response,
                                              shared_ptr<HttpServer::Request> request ) {
            if ( request.get()->path.size() > 5000 ) {
                throw "URL too long";
            }
            auto rq = make_shared<Request>(new Request);
            auto res = make_shared<Response>(new Response);
            std::function<Response( std::shared_ptr<Request> request,
                                    std::shared_ptr<Response> response )> action = Route::find(request.get()->method,
                                                                                               request.get()->path);
            auto route_response = action(rq, res);
        };
    } catch ( const exception &e ) {
        //TODO ERROR HANDLER
    }

    return 0;
}
