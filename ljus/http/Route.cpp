//
// Created by erik on 09/09/17.
//

#include <functional>
#include "Route.h"

std::function<Response( std::shared_ptr<Request> request, std::shared_ptr<Response> response )>

Route::find( std::string method, std::string path ) {

}
