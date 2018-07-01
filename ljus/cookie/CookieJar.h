//
// Created by erik on 08/09/17.
//

#ifndef LJUS_COOKIEJAR_H
#define LJUS_COOKIEJAR_H

#include <string>
#include <queue>
#include <unordered_map>

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

    /**
     *
     * @param name
     * @param value
     * @param minutes
     * @param path
     * @param domain
     * @param secure
     * @param httpOnly
     * @param raw
     * @param sameSite
     * @return
     */
    Cookie make(std::string name, std::string value, int minutes = 0, std::string path = std::string(), std::string domain = std::string(),
                bool secure = false, bool httpOnly = true, bool raw = false, std::string sameSite = std::string());

    /**
     *
     * @param name
     * @param value
     * @param path
     * @param domain
     * @param secure
     * @param httpOnly
     * @param raw
     * @param sameSite
     * @return
     */
    Cookie forever(std::string name, std::string value, std::string path = std::string(), std::string domain = std::string(), bool secure = false,
            bool httpOnly = true, bool raw = false, std::string sameSite = std::string());
    /**
     *
     * @param name
     * @param path
     * @param domain
     * @return
     */
    Cookie forget(std::string name, std::string path = std::string(), std::string domain = std::string());

    /**
     * Check if a given cookie is queued to be attached to the response
     * @param name
     * @return
     */
    bool hasQueued(std::string name);

    /**
     * Enqueue a cookie to be attached to the response
     * @param cookie the cookie to be attached
     */
    void queue(Cookie cookie);

    /**
     * Remove the given cookie from the queue of cookies that are to be attached to the response
     * @param name the name of the cookie to remove
     * @return the cookie that was removed
     */
    Cookie dequeue(std::string name);

private:
    std::unordered_map<std::string, Cookie> cookieQueue;

    std::string *getPathAndDomain(std::string path, std::string domain, bool secure, std::string sameSite);

    std::string path;
    std::string domain;
    bool secure;
    std::string sameSite;
};

#endif //LJUS_COOKIEJAR_H
