//
// Created by erik on 03/09/17.
//

#include "nacl_wrapper.h"


string Ljus::Crypt_Wrapper::crypto_secretbox_wrapper_easy(const string &m, const string &n, const string &k) {
    if (k.size() != crypto_secretbox_KEYBYTES) throw "incorrect key length";
    if (n.size() != crypto_secretbox_NONCEBYTES) throw "incorrect nonce length";
    size_t mlen = m.size() + crypto_secretbox_ZEROBYTES;
    unsigned char mpad[mlen];
    for (int i = 0;i < crypto_secretbox_ZEROBYTES;++i) mpad[i] = 0;
    for (int i = crypto_secretbox_ZEROBYTES;i < mlen;++i) mpad[i] = m[i - crypto_secretbox_ZEROBYTES];
    unsigned char cpad[mlen];
    crypto_secretbox_easy(cpad,mpad,mlen,(const unsigned char *) n.c_str(),(const unsigned char *) k.c_str());
    return string(
            (char *) cpad + crypto_secretbox_BOXZEROBYTES,
            mlen - crypto_secretbox_BOXZEROBYTES
    );
}

string Ljus::Crypt_Wrapper::crypto_secretbox_wrapper_open_easy(const string &c, const string &n, const string &k) {
    if (k.size() != crypto_secretbox_KEYBYTES) throw "incorrect key length";
    if (n.size() != crypto_secretbox_NONCEBYTES) throw "incorrect nonce length";
    size_t clen = c.size() + crypto_secretbox_BOXZEROBYTES;
    unsigned char cpad[clen];
    for (int i = 0;i < crypto_secretbox_BOXZEROBYTES;++i) cpad[i] = 0;
    for (int i = crypto_secretbox_BOXZEROBYTES;i < clen;++i) cpad[i] = c[i - crypto_secretbox_BOXZEROBYTES];
    unsigned char mpad[clen];
    if (crypto_secretbox_open(mpad,cpad,clen,(const unsigned char *) n.c_str(),(const unsigned char *) k.c_str()) != 0)
        throw "ciphertext fails verification";
    if (clen < crypto_secretbox_ZEROBYTES)
        throw "ciphertext too short"; // should have been caught by _open
    return string(
            (char *) mpad + crypto_secretbox_ZEROBYTES,
            clen - crypto_secretbox_ZEROBYTES
    );
}
