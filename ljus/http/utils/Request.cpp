
#include <cookie/CookieJar.h>
#include "Request.h"

std::vector<Cookie> Ljus::Request::get_cookies() {
    return this->cookies;
}
