//
// Created by erik on 06/09/17.
//

#ifndef LJUS_SODIUM_FUZZ_H
#define LJUS_SODIUM_FUZZ_H

#include <cassert>
#include "../ljus/encryption/Crypt.h"

using namespace Ljus;


int main(int argc, char * argv[]){
    string plain = string(argv[0]);
    string encrypted = Crypt::encrypt(plain);
    assert(Crypt::decrypt(encrypted) == plain);
    return 0;
}


#endif //LJUS_SODIUM_FUZZ_H
