//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

extern "C" {
#include "sodium.h"
};
#define HASHLEN 32
#define SALTLEN 16
#define T_COST 4
#define PARALLELISM 2
//1 MiB -- roughly going standard as of Sep 2017
#define M_COST 32000

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
