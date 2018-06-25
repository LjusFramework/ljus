//
// Created by Erik A. Partridge on 6/24/18.
//

#include <encryption/Crypt.h>
#include "EncryptCookies.h"

using namespace Ljus;

EncryptCookies::EncryptCookies(vector<string> except) {

    this->exceptions = std::move(except);

}

void EncryptCookies::disableFor(string disable) {
    this->exceptions.push_back(disable);
}

Ljus::Request EncryptCookies::decrypt(Request req) {
    for (Cookie c: req.get_cookies()) {
        if (!isDisabled(c.name)) {
            c.value = Crypt::decrypt(c.value);
        }
    }
    return req;
}

Ljus::Response Ljus::EncryptCookies::after(Response res) {
    return encrypt(res);
}

Cookie EncryptCookies::duplicate(Cookie cookie, string value) {
    Cookie newCookie = cookie;
    newCookie.value = std::move(value);
    return newCookie;
}

Cookie EncryptCookies::decryptCookie(Cookie cookie) {
    if (!isDisabled(cookie.name)) {
        cookie.value = Crypt::decrypt(cookie.value);
    }
    return cookie;
}

bool EncryptCookies::isDisabled(string cookie) {
    return std::find(exceptions.begin(), exceptions.end(), cookie) != exceptions.end();
}

Ljus::Response EncryptCookies::encrypt(Ljus::Response res) {
    for (Cookie c: res.get_cookies()) {
        if (!isDisabled(c.name)) {
            c.value = Crypt::encrypt(c.value);
        }
    }
    return res;
}

Request EncryptCookies::before(Ljus::Request req) {
    return decrypt(req);
}

Cookie EncryptCookies::encryptCookie(Cookie cookie) {
    cookie.value = Crypt::encrypt(cookie.value);
    return cookie;
}

