//
// Created by Erik A. Partridge on 7/19/18.
//

#ifndef LJUS_DATEMIDDLEWARE_H
#define LJUS_DATEMIDDLEWARE_H

#include <http/utils/Request.h>
#include <http/utils/Response.h>
#include "Middleware.h"
#include <ctime>

namespace Ljus{
    class DateMiddleware : public Middleware {
        int before(Request &req, Response &res);
        int after(Request &req, Response &res);
    };
}

#endif //LJUS_DATEMIDDLEWARE_H
