//
// Created by cents on 24/08/17.
//

#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include <vector>
#include <random>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
#include "sodium.h"
};

#include "base64.h"

#include "json.hpp"
#include "../../config.hpp"

namespace Ljus {

    class Crypt {

    public:
        static std::string encrypt( std::string value );

        static std::string decrypt( std::string combined );
    };
}

#endif //CRYPT_H
