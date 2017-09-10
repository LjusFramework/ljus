//
// Created by erik on 08/09/17.
//

#include "Request.h"


std::unordered_map<string, string> parse_params( Pistache::Http::Request request ) {
    std::unordered_map<string, string> params;
    printf("%s\n", request.body().c_str());
    return params;
}

Ljus::Request::Request( Pistache::Http::Request request ) {
    switch ( request.method()) {
        case Http::Method::Get:
            this->method = "GET";
            break;
        case Http::Method::Post:
            this->method = "POST";
            break;
        case Http::Method::Delete:
            this->method = "DELETE";
            break;
        case Http::Method::Options:
            break;
        case Http::Method::Head:
            break;
        case Http::Method::Put:
            this->method = "PUT";
            break;
        case Http::Method::Patch:
            this->method = "PATCH";
            break;
        case Http::Method::Trace:
            break;
        case Http::Method::Connect:
            break;
    }

    this->body = request.body();
    this->headers = request.headers();
    this->resource = request.resource();
    parse_params(request);

}
