//
// Created by cents on 24/08/17.
//

#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include "../../config.h"
#include <string.h>

extern "C" {
    #include <sodium.h>
}


class Crypt {

public:
    static std::string make(std::string value);
    static std::string decrypt(std::string ciphertext);

};


#endif //CRYPT_H
