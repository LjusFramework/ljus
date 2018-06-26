//
// Created by erik on 08/09/17.
//

#ifndef LJUS_COOKIEJAR_H
#define LJUS_COOKIEJAR_H

#include "http/http.h"
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
using namespace http;

struct Cookie {
    string name;
    string value;
    int minutes;
    string path;
    string domain;
    bool secure;
    bool httpOnly;
    bool raw;
    string sameSite;
};

class CookieJar {
public:
    Cookie make(string name, string value, int minutes = 0, string path = std::string(), string domain = std::string(),
                bool secure = false, bool httpOnly = true, bool raw = false, string sameSite = std::string());

    Cookie
    forever(string name, string value, string path = std::string(), string domain = std::string(), bool secure = false,
            bool httpOnly = true, bool raw = false, string sameSite = std::string());

    Cookie forget(string name, string path = std::string(), string domain = std::string());

    bool hasQueued(string name);

    void queue(Cookie cookie);

    Cookie dequeue(string name);

private:
    unordered_map<string, Cookie> cookieQueue;

    string *getPathAndDomain(string path, string domain, bool secure, string sameSite);

    string path;
    string domain;
    bool secure;
    string sameSite;
};

#endif //LJUS_COOKIEJAR_H