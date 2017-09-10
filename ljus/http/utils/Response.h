//
// Created by erik on 09/09/17.
//

#ifndef LJUS_RESPONSE_H
#define LJUS_RESPONSE_H

#include <string>
#include <unordered_map>
#include "../../../external/server/utility.hpp"

class Response {
public:

    std::string generate();

    unsigned long long content_length();

    SimpleWeb::CaseInsensitiveMultimap get_headers();

private:
    std::unordered_map<std::string, std::string> headers;
    std::string content;
    unsigned short code;
    std::string http_type = "HTTP/1.1";

};

#endif //LJUS_RESPONSE_H
