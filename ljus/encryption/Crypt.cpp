#include "Crypt.h"

int Crypt::init(){
  if(sodium_init() == -1){
    return -1;
  } else {
    
  }
}
