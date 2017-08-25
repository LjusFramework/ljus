//
// Created by cents on 24/08/17.
//

#ifndef CRYPT_H
#define CRYPT_H

#include <string>

extern "C"{
  #include <sodium.h>
}
using namespace std;

class Crypt {

public:
    static std::string make(string value);
    static std::string check(string plain, string hashed);

private:
    static int init();
};


#endif //CRYPT_H
