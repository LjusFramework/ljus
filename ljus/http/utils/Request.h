//
// Created by erik on 08/09/17.
//

#ifndef LJUS_REQUEST_H
#define LJUS_REQUEST_H

#include "encryption/Crypt.h"

namespace Ljus {
    class Request {

    public:
        std::string method;
        std::string body;
        std::string resource;

    };
}
#endif //LJUS_REQUEST_H
