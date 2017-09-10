//
// Created by cents on 24/08/17.
//

#ifndef LJUS_HANDLER_H
#define LJUS_HANDLER_H

#include <pistache/http.h>
#include <http/utils/Request.h>
#include "../encryption/Crypt.h"

using namespace Pistache;

class LjusHandler : public Pistache::Http::Handler {

public:
HTTP_PROTOTYPE(LjusHandler)

    void onRequest( const Http::Request &request, Http::ResponseWriter response ) {
        Ljus::Request req = Ljus::Request(request);
        std::string enc = Ljus::Crypt::encrypt(( std::string ) std::string("Hello world"));
        response.send(Http::Code::Ok, request.resource());

    }

};


#endif //LJUS_HANDLER_H
