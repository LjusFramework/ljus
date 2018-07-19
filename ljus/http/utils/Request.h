//
// Created by erik on 08/09/17.
//

#ifndef LJUS_REQUEST_H
#define LJUS_REQUEST_H

#include <vector>
#include <cookie/CookieJar.h>
#include <civetweb/include/civetweb.h>
#include <map>

namespace Ljus {
    class Request {
    public:
        explicit Request(struct mg_connection *conn);
        std::vector<Ljus::Cookie> get_cookies();

    private:
        std::vector<Ljus::Cookie> cookies;
        const char* raw_content;
        std::string user_ip;
        std::string method;
        std::string path;
        bool secure;
        std::map<std::string, std::string> headers;
        std::string query_string;
        std::string content;
    };
}

#endif //LJUS_REQUEST_H
