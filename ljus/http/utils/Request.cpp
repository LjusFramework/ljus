//
// Created by erik on 08/09/17.
//

#include "Request.h"

Request::Request( Pistache::Http::Request request ) {
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


}
