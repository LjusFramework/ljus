//
// Created by cents on 24/08/17.
//

#ifndef CRYPT_H
#define CRYPT_H

#include "../../config.hpp"
#include <string>
#include <vector>
#include "crypto_secretbox_xsalsa20poly1305.h"
#include "json.hpp"
#include <fcntl.h>
#include <unistd.h>
#include "cppcodec/base64_rfc4648.hpp"

using base64 = cppcodec::base64_rfc4648;

namespace Ljus{
    
    class Crypt {

    public:
        static std::string encrypt(std::string value);
        static std::string decrypt(std::string ciphertext);

    };
}

#endif //CRYPT_H
