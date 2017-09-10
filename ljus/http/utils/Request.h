//
// Created by erik on 08/09/17.
//

#ifndef LJUS_REQUEST_H
#define LJUS_REQUEST_H

#include <pistache/http.h>
#include "encryption/Crypt.h"

using namespace Pistache;
namespace Ljus {
    class Request {

    public:
        explicit Request( Pistache::Http::Request request );

        std::string method;
        std::string body;
        std::string resource;
        Http::Header::Collection headers;

    };
}
#endif //LJUS_REQUEST_H
