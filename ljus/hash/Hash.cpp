//
// Created by Erik Partridge on 24/08/17.
//

#include <sodium.h>
#include "Hash.h"


using namespace std;

string Ljus::Hash::make( string pwd ) {

    const char *value = pwd.c_str();

    uint8_t salt[SALTLEN];
    int fd = open("/dev/urandom", O_RDONLY);
    ssize_t size = read(fd, salt, sizeof salt);
    if ( size != sizeof salt ) {
        throw "Could not generate salt";
    }
    close(fd);

    unsigned long pwdlen = strlen(value);
    char encoded[97];
    if (crypto_pwhash_str(encoded, value, pwdlen, crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw "Out of memory";
    }
    return string(strdup(encoded));
}


bool Ljus::Hash::check( string plain, string hashed ) {
    return crypto_pwhash_str_verify(hashed.c_str(), plain.c_str(), strlen(plain.c_str())) == 0;
}

bool Ljus::Hash::needs_rehash( string hashed ) {
    return crypto_pwhash_str_needs_rehash(hashed.c_str(), crypto_pwhash_OPSLIMIT_INTERACTIVE,
                                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0;
}
