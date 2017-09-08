//
// Created by cents on 24/08/17.
//

#ifndef CRYPT_H
#define CRYPT_H

#include "../../config.hpp"
#include <string>
#include <vector>
extern "C"{
#include "sodium.h"
#include "base64.h"
};
#include "json.hpp"
#include <fcntl.h>
#include <unistd.h>

//using base64 = cppcodec::base64_rfc4648;

namespace Ljus{
    
    class Crypt {

    public:
        static std::string encrypt(std::string value);
        static std::string decrypt(std::string combined);
    };
}

#endif //CRYPT_H
