#include "Crypt.h"
#include <string.h>

using namespace std;


string Crypt::make(string value){
if(sodium_init() == -1){
    return "-6";
  }

  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  unsigned char encrypted[crypto_secretbox_MACBYTES + strlen(value.c_str()) + 1];
  std::string app_key = config["app_key"].get<std::string>();
  if(strlen(app_key.c_str()) < crypto_secretbox_KEYBYTES){
    //TODO Error
  }

  randombytes_buf(nonce, sizeof nonce);
  crypto_secretbox_easy(encrypted, (const unsigned char*) value.c_str(), strlen(value.c_str()),
                        nonce, (const unsigned char*) app_key.c_str());
  return string(to_hex(hex, encrypted));
  /*std::string ciphertext(reinterpret_cast<char * const> (encrypted));
  std::string nonce_str(reinterpret_cast<char* const> (nonce));
  std::string result = "nonce=" + nonce_str + ";value=" + ciphertext + ";";
  return result;*/
}

string Crypt::decrypt(std::string ciphertext) {
  printf(ciphertext.c_str());
  string delimiter = ";value=";
  std::string app_key = config["app_key"].get<std::string>();
  printf(ciphertext.substr(6, ciphertext.find(delimiter)).c_str()); printf("\n");
  printf(ciphertext.substr(ciphertext.find(delimiter) + 6, ciphertext.length() - 1).c_str()); printf("\n");
  const unsigned char * nonce = (const unsigned char*) ciphertext.substr(6, ciphertext.find(delimiter)).c_str();
  const unsigned char * enc = (const unsigned char*) ciphertext.substr(ciphertext.find(delimiter) + 6, ciphertext.length() - 1).c_str();
  if(sodium_init() == -1){
    return "-5";
  }
  unsigned long long length = ciphertext.length();
  unsigned char result[length];
  int res = crypto_secretbox_open_easy(result, enc, length, nonce, (const unsigned char *)app_key.c_str());
  string str_res = string(reinterpret_cast<char * const> (result));
  return str_res;

}
