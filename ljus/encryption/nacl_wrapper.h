//
// Created by erik on 03/09/17.
//

#ifndef LJUS_NACL_WRAPPER_H
#define LJUS_NACL_WRAPPER_H
#include <string>
extern "C" {
    #include "sodium.h"
};

using std::string;

namespace Ljus{

    class Crypt_Wrapper{
        public:
            static string crypto_secretbox_wrapper_easy(const string &m, const string &n, const string &k);
            static string crypto_secretbox_wrapper_open_easy(const string &c, const string &n, const string &k);

    };
}


#endif //LJUS_NACL_WRAPPER_H
