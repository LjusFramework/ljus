//
// Created by erik on 08/09/17.
//

#ifndef LJUS_COOKIEJAR_H
#define LJUS_COOKIEJAR_H

static const int FIVE_YEARS = 2628000;

#include <string>
#include <queue>
#include <unordered_map>
#include <sstream>

namespace Ljus {
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
    Ljus::Cookie make(std::string name, std::string value, int minutes = 0, std::string path = std::string(),
            std::string domain = std::string(),
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
    Ljus::Cookie forever(std::string name, std::string value, std::string path = std::string(),
            std::string domain = std::string(), bool secure = false,
            bool httpOnly = true, bool raw = false, std::string sameSite = std::string());
    /**
     *
     * @param name
     * @param path
     * @param domain
     * @return
     */
    Ljus::Cookie forget(std::string name, std::string path = std::string(), std::string domain = std::string());

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
    void queue(Ljus::Cookie cookie);

    /**
     * Remove the given cookie from the queue of cookies that are to be attached to the response
     * @param name the name of the cookie to remove
     * @return the cookie that was removed
     */
    Ljus::Cookie dequeue(std::string name);

private:
    std::unordered_map<std::string, Ljus::Cookie> cookieQueue;

    std::string* getPathAndDomain(std::string path, std::string domain, bool secure, std::string sameSite);

    std::string path;
    std::string domain;
    bool secure;
    std::string sameSite;
};
}
#endif //LJUS_COOKIEJAR_H
