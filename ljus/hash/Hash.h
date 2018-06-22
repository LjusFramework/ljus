//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H
extern "C" {
#include "sodium.h"
};
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

#define HASHLEN 32
#define SALTLEN 16

using namespace std;

namespace Ljus {

    class Hash {

    public:
        static string make( string value );

        static bool check( string plain, string hashed );

        static bool needs_rehash( string hashed );
    };
}

#endif //HASH_H
