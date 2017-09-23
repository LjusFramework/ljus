
#include "Crypt.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Generate a nonce based on the present time and a randomly shuffled string
 * @return a 24 char nonce
 */
string get_nonce() {
    string base = "ABCDEFGHIJKLMNOPQRSTOUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    unsigned long long time = ( unsigned long long ) (system_clock::now().time_since_epoch() / milliseconds(1));
    shuffle(base.begin(), base.end(), std::mt19937(std::random_device()()));
    base = to_string(time) + base;
    return base.substr(0, crypto_secretbox_NONCEBYTES);
}

/**
 * @brief Encrypt a given string
 * @param m the content to encrypt in string form.
 * @return the encrypted string in base 64 format (nonce will be included)
 */
string Ljus::Crypt::encrypt( string m ) {
    if ( sodium_init() < 0 ) {
        throw "Couldn't init libsodium";
    }
    string key = config["app_key"].get<string>().substr(0, 32);
    string nonce = get_nonce();

    if ( key.size() != crypto_secretbox_KEYBYTES ) {
        throw "incorrect key length";
    }
    unsigned long long message_length = m.size() + crypto_secretbox_ZEROBYTES;
    unsigned char message[message_length];
    for ( size_t i = 0; i < crypto_secretbox_ZEROBYTES; ++i ) {
        message[i] = 0;
    }
    for ( size_t i = crypto_secretbox_ZEROBYTES; i < message_length; ++i ) {
        message[i] = static_cast<unsigned char>(m[i - crypto_secretbox_ZEROBYTES]);
    }
    unsigned char ciphertext[message_length];
    crypto_secretbox(ciphertext, message, message_length, ( const unsigned char * ) nonce.c_str(),
                     ( const unsigned char * ) key.c_str());
    string crypt = string(( char * ) ciphertext + crypto_secretbox_BOXZEROBYTES,
                          message_length - crypto_secretbox_BOXZEROBYTES);
    string raw = nonce + ";&c=" + crypt;
    string result;
    Base64::Encode(raw, &result);
    return result;
}

/**
 * @brief Decrypt a string as encrypted using the built-in encrypt function
 * @param raw the encrypted string
 * @return the decrypted version of the string -- your original content
 */
string Ljus::Crypt::decrypt( std::string raw ) {
    string combined;
    Base64::Decode(raw, &combined);

    string key = config["app_key"].get<string>().substr(0, 32);

    if ( sodium_init() < 0 ) {
        throw "Couldn't init libsodium";
    }

    string nonce;
    string ciphertext;
    nonce = combined.substr(0, combined.find(";&c="));
    ciphertext = combined.substr(combined.find(";&c=") + 4, combined.length());
    if ( key.size() != crypto_secretbox_KEYBYTES ) {
        throw "Invalid key length";
    }

    unsigned long long ciphertext_length = ciphertext.size() + crypto_secretbox_BOXZEROBYTES;
    unsigned char ciphertext_padding[ciphertext_length];
    for ( size_t i = 0; i < crypto_secretbox_BOXZEROBYTES; ++i ) {
        ciphertext_padding[i] = 0;
    }
    for ( size_t i = crypto_secretbox_BOXZEROBYTES; i < ciphertext_length; ++i ) {
        ciphertext_padding[i] = static_cast<unsigned char>(ciphertext[i - crypto_secretbox_BOXZEROBYTES]);
    }
    unsigned char message[ciphertext_length];

    if ( crypto_secretbox_open(message, ciphertext_padding, ciphertext_length, ( const unsigned char * ) nonce.c_str(),
                               ( const unsigned char * ) key.c_str()) != 0 ) {
        throw "ciphertext fails verification";
    }
    if ( ciphertext_length < crypto_secretbox_ZEROBYTES) {
        throw "ciphertext too short";
    }
    return string(( char * ) message + crypto_secretbox_ZEROBYTES, ciphertext_length - crypto_secretbox_ZEROBYTES);
}