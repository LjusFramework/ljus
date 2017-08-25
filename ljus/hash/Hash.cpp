//
// Created by Erik Partridge on 24/08/17.
//

#include "Hash.h"
#include <stdio.h>
#include <string.h>

using namespace std;

string Hash::make(string value) {
  if(sodium_init() == -1){
    //TODO ERROR
  }
  char *result = new char[crypto_pwhash_STRBYTES];
  //Use sensible defaults, can be reduced to sensitive or increased if need be
  if(crypto_pwhash_str(result, value.c_str(), (unsigned) strlen(value.c_str()),
    crypto_pwhash_opslimit_moderate(), crypto_pwhash_memlimit_moderate()) != 0){
      //Handle out of memory error
  }
  string str_result = string(result);
  delete[] result;
  return str_result;
}

string Hash::check(string plain, string hashed) {
  if(sodium_init() == -1){
    //TODO Error
  }
  return crypto_pwhash_str_verify(plain.c_str(), hashed.c_str(), (unsigned) strlen(hashed.c_str()));
}
