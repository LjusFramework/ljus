//
// Created by Erik A. Partridge on 7/2/18.
//

#ifndef LJUS_ZEROENTROPYERROR_H
#define LJUS_ZEROENTROPYERROR_H


#include <exception>

namespace Ljus {
    namespace Exceptions {
        struct ZeroEntropyError : public std::exception {
            const char * what () const throw () {
                return "Unable to secure bytes from /dev/urandom";
            }
        };
    }
}


#endif //LJUS_ZEROENTROPYERROR_H
