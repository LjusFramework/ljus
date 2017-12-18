#ifndef NOSUCHFILEERROR
#define NOSUCHFILEERROR
// Write your header file here.
#include <exception>

namespace Ljus {
    namespace Exceptions {
       struct NoSuchFileError : public std::exception {
           const char * what () const throw () {
              return "No such file";
           }
        }; 
    }
}
#endif