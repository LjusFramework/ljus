//
// Created by Erik A. Partridge on 7/19/18.
//

#ifndef LJUS_MIDDLEWARE_H
#define LJUS_MIDDLEWARE_H
#include <http/utils/Request.h>
#include <http/utils/Response.h>

namespace Ljus {

    class Middleware {
    public:
        virtual int before(Request &req, Response &res) = 0;
        virtual int after(Request &req, Response &res) = 0;
    };

}

#endif //LJUS_MIDDLEWARE_H
