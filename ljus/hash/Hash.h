//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H

#include <string>
#include <argon2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

#define HASHLEN 32
#define SALTLEN 16
#define T_COST 5
#define PARALLELISM 3
#define M_COST 48000

using namespace std;

namespace Ljus {

    class Hash {

    public:
        /**
         * Securely hash a plain text value, using the argon2 ref spec implementation
         * @param value the plain text value. Please don't store this.
         * @return the argon2 hashed and salted string
         */
        static string make( string value );

        /**
         * Check if the plain value and hashed value are at their core, equivalent.
         * @param plain the plain text value
         * @param hashed the stored hashed and salted string
         * @return equivalency
         */
        static bool check( string plain, string hashed );

        /**
         * Check if a hash needs to be rehashed. This is generally a check as to if the work factor has increased since the last time this was run.
         * We recommend running this every time a user logs in, checking for equivalency, and if the user entered the correct password, hashing their input with the new work factor.
         * Most often, this will happen because you updated your copy of Ljus and the standards have changed. Updating the work factor is not considered a breaking change, however, failure to check for rehashing in your authentication approach may cause loss of security and breaking effects.
         * @param hashed the hashed value
         * @return if a value needs to be rehashed
         */
        static bool needs_rehash( string hashed );
    };
}

#endif //HASH_H
