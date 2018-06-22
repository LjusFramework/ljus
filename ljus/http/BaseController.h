//
// Created by erik on 23/09/17.
//

#ifndef LJUS_BASECONTROLLER_H
#define LJUS_BASECONTROLLER_H


#include <http/utils/Response.h>
#include <http/utils/Request.h>
#include <memory>

class BaseController {

public:
    Response index( std::shared_ptr<Request> req, std::shared_ptr<Response> res ) {

    }

};


#endif //LJUS_BASECONTROLLER_H
