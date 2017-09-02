
#include "Crypt.h"

using namespace std;

string Ljus::Crypt::encrypt(string value){
  //Key needs to be 32 chars-- 256 bit for xsalsa
  string key = config["app_key"].get<string>().substr(0,32);
  string nonce = "012345678901234567890123";
  string ciphertext;
  //Get secure "real" random for the nonce
  uint8_t nonce_raw[24];
  int fd = open("/dev/random", O_RDONLY);
  int size = read(fd, nonce_raw, sizeof nonce_raw);
  close(fd);
  nonce = base64::encode(nonce_raw, 24);
  //Perform the encryption, xsalsa20 is used to avoid limitations of 256-GCM
  ciphertext = crypto_secretbox_xsalsa20poly1305(value, nonce.substr(0,24), key);
  //Pack it into a JSON for nice storage
  json output;
  output["nonce"] = nonce.substr(0,24);
  output["content"] = base64::encode(ciphertext);
  string stringified = output.dump();
  return base64::encode(stringified);
}

string Ljus::Crypt::decrypt(std::string ciphertext) {
  vector<unsigned char> decoded_chars = base64::decode(ciphertext);
  string decoded = string(decoded_chars.begin(), decoded_chars.end());
  json parsed = json::parse(decoded);

  vector<unsigned char> decoded_value = base64::decode(parsed["content"].get<string>());
  string content = string(decoded_value.begin(), decoded_value.end());
  string key = config["app_key"].get<string>().substr(0,32);

  string plain = crypto_secretbox_xsalsa20poly1305_open(content, parsed["nonce"].get<string>(), key);
  return plain;
}
