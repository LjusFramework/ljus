//
// Created by erik on 08/09/17.
//

#ifndef LJUS_COOKIEJAR_H
#define LJUS_COOKIEJAR_H

#include "http/http.h"
#include <string>
#include <queue>
#include <unordered_map>

using namespace http;

struct Cookie {
    std::string name;
    std::string value;
    int minutes;
    std::string path;
    std::string domain;
    bool secure;
    bool httpOnly;
    bool raw;
    std::string sameSite;
};

class CookieJar {
public:
    Cookie make(std::string name, std::string value, int minutes = 0, std::string path = std::string(), std::string domain = std::string(),
                bool secure = false, bool httpOnly = true, bool raw = false, std::string sameSite = std::string());

    Cookie
    forever(std::string name, std::string value, std::string path = std::string(), std::string domain = std::string(), bool secure = false,
            bool httpOnly = true, bool raw = false, string sameSite = std::string());

    Cookie forget(std::string name, std::string path = std::string(), std::string domain = std::string());

    bool hasQueued(std::string name);

    void queue(Cookie cookie);

    Cookie dequeue(std::string name);

private:
    unordered_map<std::string, Cookie> cookieQueue;

    std::string *getPathAndDomain(std::string path, std::string domain, bool secure, std::string sameSite);

    std::string path;
    std::string domain;
    bool secure;
    std::string sameSite;
};

#endif //LJUS_COOKIEJAR_H
