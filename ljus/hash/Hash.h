//
// Created by cents on 24/08/17.
//

#ifndef HASH_H
#define HASH_H

#include <string>

extern "C"{
  #include <sodium.h>
}
using namespace std;

class Hash {

public:
    static std::string make(string value);
    static std::string check(string plain, string hashed);
};


#endif //HASH_H
