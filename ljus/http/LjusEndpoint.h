//
// Created by cents on 24/08/17.
//

#ifndef LJUS_ENDPOINT_H
#define LJUS_ENDPOINT_H

#include <pistache/http.h>
#include <pistache/endpoint.h>
#include "../encryption/Crypt.h"
#include "LjusHandler.h"

using namespace Pistache;

class LjusEndpoint : public Pistache::Http::Endpoint {

public:
    HTTP_PROTOTYPE(LjusHandler)

    void onRequest( const Http::Request &request, Http::ResponseWriter response ) {
        std::string enc = Ljus::Crypt::encrypt((std::string) std::string("Hello world"));
        response.send(Http::Code::Ok, enc);
    }

};


#endif //LJUS_ENDPOINT_H
