//
// Created by Erik Partridge on 24/08/17.
//

#include "Hash.h"


using namespace std;

string Ljus::Hash::make( string pwd ) {

    const char *value = pwd.c_str();

    uint8_t salt[SALT_LENGTH];
    int fd = open("/dev/urandom", O_RDONLY);
    ssize_t size = read(fd, salt, sizeof salt);
    if ( size != sizeof salt ) {
        throw Exceptions::ZeroEntropyError();
    }
    close(fd);

    unsigned long pwdlen = strlen(value);
    char encoded[97];

    argon2i_hash_encoded(T_COST, M_COST, PARALLELISM, value, pwdlen, salt, SALT_LENGTH, HASH_LENGTH, encoded, 97);

    std::string res = encoded;
    return res;
}


bool Ljus::Hash::check( string plain, string hashed ) {
    return argon2i_verify(hashed.c_str(), plain.c_str(), strlen(plain.c_str())) == 0;
}

bool Ljus::Hash::needs_rehash( string hashed ) {
    std::ostringstream settings;
    settings << "$m=" << M_COST << ",t=" << T_COST << ",p=" << PARALLELISM;
    unsigned long index = hashed.find(settings.str());
    return index >= hashed.length();
}
