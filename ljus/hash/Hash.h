//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H

#include <string>

using namespace std;

namespace Ljus{
        
    class Hash {

    public:
        static string make(string value);
        static bool check(string plain, string hashed);
        static bool needs_rehash(string hashed);
    };
}

#endif //HASH_H
