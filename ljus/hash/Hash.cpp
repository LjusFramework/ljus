//
// Created by Erik Partridge on 24/08/17.
//

#include "Hash.h"
#include <string.h>
#include "argon2.h"
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
using namespace std;

#define HASHLEN 32
#define SALTLEN 16
#define T_COST 2
#define PARALLELISM 2

string Hash::make(string pwd) {

  const char* value = pwd.c_str();
  
  uint8_t salt[SALTLEN];
  int fd = open("/dev/random", O_RDONLY);
  int size = read(fd, salt, sizeof salt);
  close(fd);

  uint32_t pwdlen = strlen(value);
  //1 MiB -- this is roughly the going standard as of Sep 2017
  uint32_t m_cost = (1<<16);
  char encoded[97];
  
  argon2i_hash_encoded(T_COST, m_cost, PARALLELISM, value, pwdlen, salt, SALTLEN,HASHLEN, encoded, 97);
  return string(strdup(encoded));
}


bool Hash::check(string plain, string hashed) {
  return argon2i_verify(hashed.c_str(), plain.c_str(), strlen(plain.c_str())) == 0;
}

bool Hash::needs_rehash(string hashed){
  
}
