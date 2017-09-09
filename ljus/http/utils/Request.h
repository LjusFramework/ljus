//
// Created by erik on 08/09/17.
//

#ifndef LJUS_REQUEST_H
#define LJUS_REQUEST_H

#include <pistache/http.h>
#include "encryption/Crypt.h"

using namespace Pistache;

class Request {

public:
    explicit Request( Pistache::Http::Request request );

    std::string method;
    std::string body;
    Http::Header::Collection headers;

};

#endif //LJUS_REQUEST_H
