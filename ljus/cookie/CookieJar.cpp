//
// Created by erik on 08/09/17.
//

#include "CookieJar.h"

void CookieJar::queue(Cookie cookie) {
    this->cookieQueue.emplace(cookie.name, cookie);
}

Cookie CookieJar::make(string name, string value, int minutes, string path, string domain, bool secure, bool httpOnly,
                       bool raw, string sameSite) {
    string *pathAndDomain = getPathAndDomain(path, domain, secure, sameSite);

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

string *CookieJar::getPathAndDomain(string path, string domain, bool secure, string sameSite) {
    string result[4];
    string rpath = (path.empty() ? this->path : path);
    string rdomain = (domain.empty() ? this->domain : domain);
    bool rsecure = (!secure ? this->secure : secure);
    string ssecure = (rsecure ? "1" : "0");
    string rsameSite = (sameSite.empty() ? this->sameSite : sameSite);
    result[0] = rpath;
    result[1] = rdomain;
    result[2] = ssecure;
    result[3] = rsameSite;
    return result;
}

Cookie CookieJar::forever(string name, string value, string path, string domain, bool secure, bool httpOnly, bool raw,
                          string sameSite) {
    const int FIVE_YEARS = 2628000;
    return this->make(name, value, FIVE_YEARS, path, domain, secure, httpOnly, raw, sameSite);
}

Cookie CookieJar::forget(string name, string path, string domain) {
    const int NEG_FIVE_YEARS = -1 * 2628000;
    return this->make(name, std::string(), NEG_FIVE_YEARS, path, domain);
}

bool CookieJar::hasQueued(string name) {
    return this->cookieQueue.count(name) > 0;
}

Cookie CookieJar::dequeue(string name) {
    Cookie c = this->cookieQueue.at(name);
    this->cookieQueue.erase(name);
    return c;
}
