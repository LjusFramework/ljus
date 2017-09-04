
#include "Crypt.h"
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

string get_nonce(){
    string base = "ABCDEFGHIJKLMNOPQRSTOUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char bytes[sizeof(int) + 32];
    return base.substr(0, crypto_secretbox_NONCEBYTES);
}

string Ljus::Crypt::encrypt(string value){
    if(sodium_init() < 0){
        throw "Couldn't init libsodium";
    }
    //Key needs to be 32 chars-- 256 bit for xsalsa
    string tkey = "0123456789123456789012345678901234560";
    string key = tkey.substr(0,32);

    string nonce = get_nonce();

    //Perform the encryption, xsalsa20 is used to avoid limitations of 256-GCM
    unsigned char ciphertext[value.length() + crypto_secretbox_MACBYTES ];

    int res = crypto_secretbox_easy(ciphertext, reinterpret_cast<const unsigned char *>(value.c_str()), strlen(value.c_str()),
                                    reinterpret_cast<const unsigned char *>(nonce.c_str()),
                                    reinterpret_cast<const unsigned char *>(key.c_str()));
    printf("RES RESULT: %d\n", res);

    string content;
    content = string(reinterpret_cast<char*>(ciphertext));

    //Pack it into a JSON for nice storage
    string nonce_encoded;
    Base64::Encode(nonce, &nonce_encoded);
    string content_encoded;
    Base64::Encode(content, &content_encoded);
    json output;
    output["nonce"] = nonce_encoded;
    output["content"] = content_encoded;
    string stringified = output.dump();

    return nonce_encoded + ";&c=" + content_encoded;
}

string Ljus::Crypt::decrypt(std::string combined) {
    if(sodium_init() < 0){
        throw "Couldn't init libsodium";
    }
   // auto j = combined::parse(combined);
    string nonce_t;
    string ciphertext_t;
    string nonce;
    string ciphertext;
    nonce_t = combined.substr(0, combined.find(";&c="));
    ciphertext_t = combined.substr(combined.find(";&c=") +4, combined.length());
    Base64::Decode(ciphertext_t, &ciphertext);
    Base64::Decode(nonce_t, &nonce);/*
    vector<unsigned char> decoded_chars = base64::decode(j["content"].get<string>());

    string ciphertext = string(decoded_chars.begin(), decoded_chars.end());

    vector<unsigned char> decoded_nonce = base64::decode(j["nonce"].get<string>());

    string nonce = string(decoded_nonce.begin(), decoded_nonce.end());*/

    string tkey = "0123456789123456789012345678901234560";
    string key = tkey.substr(0,32);

    unsigned char message[ciphertext.length()];
    int plain = crypto_secretbox_open_easy(message, reinterpret_cast<const unsigned char *>(ciphertext.c_str()), strlen(ciphertext.c_str()),
                                           reinterpret_cast<const unsigned char *>(nonce.c_str()), reinterpret_cast<const unsigned char *>(key.c_str()));
    if(plain == -1){
        throw "Invalid authentication";
    }
    return string(reinterpret_cast<char*>(message));
}