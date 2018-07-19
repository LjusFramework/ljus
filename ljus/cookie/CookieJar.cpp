//
// Created by erik on 08/09/17.
//

#include "CookieJar.h"
#include <utility>
void Ljus::CookieJar::queue(Ljus::Cookie cookie) {
    this->cookieQueue.emplace(cookie.name, cookie);
}

/**
 * Make a cookie
 * @param name The name of the cookie
 * @param value the contents of the cookie
 * @param minutes the duration of the cookie
 * @param path the path for the cookie
 * @param domain the domain for it
 * @param secure if it should be https only
 * @param httpOnly if http only, ie javascript unable to read it
 * @param raw
 * @param sameSite
 * @return the constructed cookie
 */
Ljus::Cookie Ljus::CookieJar::make(std::string name, std::string value, int minutes, std::string path, std::string domain, bool secure, bool httpOnly,
                       bool raw, std::string sameSite) {
    std::string *pathAndDomain = getPathAndDomain(std::move(path), std::move(domain), secure, std::move(sameSite));

    Cookie c = Cookie();
    c.name = std::move(name);
    c.value = std::move(value);
    c.minutes = minutes;
    c.path = pathAndDomain[0];
    c.domain = pathAndDomain[1];
    std::stringstream temp(pathAndDomain[2]);
    int x = 0;
    temp >> x;
    c.secure = (bool) x;
    c.httpOnly = httpOnly;
    c.raw = raw;
    c.sameSite = pathAndDomain[3];
    delete pathAndDomain;
    return c;
}

std::string *Ljus::CookieJar::getPathAndDomain(std::string path, std::string domain, bool secure, std::string sameSite) {
    auto result = new std::string[4];
    std::string rpath = (path.empty() ? this->path : path);
    std::string rdomain = (domain.empty() ? this->domain : domain);
    bool rsecure = (!secure ? this->secure : secure);
    std::string ssecure = (rsecure ? "1" : "0");
    std::string rsameSite = (sameSite.empty() ? this->sameSite : sameSite);
    result[0] = rpath;
    result[1] = rdomain;
    result[2] = ssecure;
    result[3] = rsameSite;
    //TODO don't let the variable escape the local scope
    return result;
}

/**
 * Put a cookie on the browser for five years
 * @param name the name of the cookie to add
 * @param value the contents of the cookie
 * @param path the path for the cookie
 * @param domain the domain for the cookie
 * @param secure if the cookie should be sent only over HTTPS
 * @param httpOnly if it should be http only, not javascript accessible
 * @param raw
 * @param sameSite
 * @return the created cookie
 */
Ljus::Cookie Ljus::CookieJar::forever(std::string name, std::string value, std::string path, std::string domain, bool secure, bool httpOnly, bool raw,
                          std::string sameSite) {
    return this->make(std::move(name), std::move(value), FIVE_YEARS, std::move(path),
            std::move(domain), secure, httpOnly, raw, std::move(sameSite));
}

/**
 * Forget a cookie previously added
 * @param name the name of the cookie to forget
 * @param path the path, as previously set
 * @param domain the domain, as previously set
 * @return return a cookie that once sent to user will expire the previous one
 */
Ljus::Cookie Ljus::CookieJar::forget(std::string name, std::string path, std::string domain) {
    const int NEG_FIVE_YEARS = -1 * FIVE_YEARS;
    return this->make(name, std::string(), NEG_FIVE_YEARS, path, std::move(domain));
}

bool Ljus::CookieJar::hasQueued(std::string name) {
    return this->cookieQueue.count(name) > 0;
}

/**
 * Removes a given cookie from the list of cookies to add to the next request
 * @param name the name of the cookie to remove
 * @return the cookie that was removed
 */
Ljus::Cookie Ljus::CookieJar::dequeue(std::string name) {
    Ljus::Cookie c = this->cookieQueue.at(name);
    this->cookieQueue.erase(name);
    return c;
}
