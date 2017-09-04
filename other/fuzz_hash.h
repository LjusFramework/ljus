//
// Created by erik on 04/09/17.
//

#ifndef LJUS_FUZZ_HASH_H
#define LJUS_FUZZ_HASH_H

#include <cassert>
#include "../ljus/hash/Hash.h"

using namespace Ljus;

int main(int argc, char * argv[]){
    string plain = string(argv[0]);
    std::string hashed = Hash::make(plain);
    assert(!Hash::needs_rehash(hashed));
    assert(Hash::check(plain, hashed));
    return 0;
}


#endif //LJUS_FUZZ_HASH_H
