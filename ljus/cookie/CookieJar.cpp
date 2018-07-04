//
// Created by erik on 08/09/17.
//

#include "CookieJar.h"

void CookieJar::queue(Cookie cookie) {
    this->cookieQueue.emplace(cookie.name, cookie);
}

Cookie CookieJar::make(std::string name, std::string value, int minutes, std::string path, std::string domain, bool secure, bool httpOnly,
                       bool raw, std::string sameSite) {
    std::string *pathAndDomain = getPathAndDomain(path, domain, secure, sameSite);

    Cookie c = Cookie();
    c.name = name;
    c.value = value;
    c.minutes = minutes;
    c.path = pathAndDomain[0];
    c.domain = pathAndDomain[1];
    c.secure = (bool) atoi(pathAndDomain[2].c_str());
    c.httpOnly = httpOnly;
    c.raw = raw;
    c.sameSite = pathAndDomain[3];
    delete pathAndDomain;
    return c;
}

std::string *CookieJar::getPathAndDomain(std::string path, std::string domain, bool secure, std::string sameSite) {
    std::string* result = new std::string[4];
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

Cookie CookieJar::forever(std::string name, std::string value, std::string path, std::string domain, bool secure, bool httpOnly, bool raw,
                          std::string sameSite) {
    return this->make(name, value, FIVE_YEARS, path, domain, secure, httpOnly, raw, sameSite);
}

Cookie CookieJar::forget(std::string name, std::string path, std::string domain) {
    const int NEG_FIVE_YEARS = -1 * FIVE_YEARS;
    return this->make(name, std::string(), NEG_FIVE_YEARS, path, domain);
}

bool CookieJar::hasQueued(std::string name) {
    return this->cookieQueue.count(name) > 0;
}

/**
 *
 * @param name
 * @return
 */
Cookie CookieJar::dequeue(std::string name) {
    Cookie c = this->cookieQueue.at(name);
    this->cookieQueue.erase(name);
    return c;
}
