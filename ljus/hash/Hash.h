//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H

#include <string>

#define HASHLEN 32
#define SALTLEN 16
#define T_COST 2
#define PARALLELISM 2

using namespace std;

class Hash {

public:
    static string make(string value);
    static int check(string plain, string hashed);
};


#endif //HASH_H
