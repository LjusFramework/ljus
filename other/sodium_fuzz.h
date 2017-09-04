//
// Created by erik on 04/09/17.
//

#ifndef LJUS_SODIUM_FUZZ_H
#define LJUS_SODIUM_FUZZ_H

#include <cassert>
#include <cstring>

extern "C"{
#include "sodium.h"
};

int main(int argc, char * argv[]){
    assert(sodium_init() > -1);
    const unsigned char* nonce = (const unsigned char*)(argv[0]);
   const  unsigned char* content = (const unsigned char*)(argv[1]);

    const unsigned char* key = (const unsigned char*)(argv[2]);
    unsigned char ciphertext[sizeof content + crypto_secretbox_MACBYTES ];

    int res = crypto_secretbox_easy(ciphertext, content, sizeof content / sizeof content[0],
                                    nonce,
                                    key);
    unsigned char decrypted[sizeof content / sizeof content[0]];

    int r = crypto_secretbox_open_easy(decrypted, ciphertext, sizeof ciphertext / sizeof ciphertext[0], nonce, key);
    assert(r == 0);
    assert(memcmp(content, decrypted, sizeof(decrypted)) == 0);
    return 0;
}


#endif //LJUS_SODIUM_FUZZ_H
