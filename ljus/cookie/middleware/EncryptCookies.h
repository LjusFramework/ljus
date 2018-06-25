//
// Created by Erik A. Partridge on 6/24/18.
//

#ifndef LJUS_ENCRYPTCOOKIES_H
#define LJUS_ENCRYPTCOOKIES_H

#include <vector>
#include <string>
#include <cookie/CookieJar.h>
#include <http/utils/Request.h>
#include <http/utils/Response.h>

using namespace std;

namespace Ljus {
    class EncryptCookies {

    public:
        explicit EncryptCookies(vector<string> except);

        void disableFor(string disable);

        Request decrypt(Ljus::Request req);

        Cookie duplicate(Cookie cookie, string value);

        Response encrypt(Ljus::Response res);

        Request before(Ljus::Request req);

        Response after(Ljus::Response res);

    private:
        bool isDisabled(string cookie);

        vector<string> exceptions;

        Cookie decryptCookie(Cookie cookie);

        Cookie encryptCookie(Cookie cookie);

    };
}


#endif //LJUS_ENCRYPTCOOKIES_H
