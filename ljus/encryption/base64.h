/*
 * Copyright (C) 2013 Tomas Kislan
Copyright (C) 2013 Adam Rudd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef BASE64_H
#define BASE64_H

#include <string>

const char kBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

class Base64 {
public:
    static bool Encode( const std::string &in, std::string *out ) {
        int i = 0, j = 0;
        size_t enc_len = 0;
        unsigned char a3[3];
        unsigned char a4[4];

        out->resize(EncodedLength(in));

        unsigned long input_len = in.size();
        std::string::const_iterator input = in.begin();

        while ( input_len-- ) {
            a3[i++] = ( unsigned char ) *(input++);
            if ( i == 3 ) {
                a3_to_a4(a4, a3);

                for ( i = 0; i < 4; i++ ) {
                    (*out)[enc_len++] = kBase64Alphabet[a4[i]];
                }

                i = 0;
            }
        }

        if ( i ) {
            for ( j = i; j < 3; j++ ) {
                a3[j] = '\0';
            }

            a3_to_a4(a4, a3);

            for ( j = 0; j < i + 1; j++ ) {
                (*out)[enc_len++] = kBase64Alphabet[a4[j]];
            }

            while ((i++ < 3)) {
                (*out)[enc_len++] = '=';
            }
        }

        return (enc_len == out->size());
    }

    static bool Decode( const std::string &in, std::string *out ) {
        int i = 0;
        int j = 0;
        size_t dec_len = 0;
        unsigned char a3[3];
        unsigned char a4[4];

        unsigned long input_len = in.size();
        std::string::const_iterator input = in.begin();

        out->resize(DecodedLength(in));

        while ( input_len-- ) {
            if ( *input == '=' ) {
                break;
            }

            a4[i++] = *(input++);
            if ( i == 4 ) {
                for ( i = 0; i < 4; i++ ) {
                    a4[i] = b64_lookup(a4[i]);
                }

                a4_to_a3(a3, a4);

                for ( i = 0; i < 3; i++ ) {
                    (*out)[dec_len++] = a3[i];
                }

                i = 0;
            }
        }

        if ( i ) {
            for ( j = i; j < 4; j++ ) {
                a4[j] = '\0';
            }

            for ( j = 0; j < 4; j++ ) {
                a4[j] = b64_lookup(a4[j]);
            }

            a4_to_a3(a3, a4);

            for ( j = 0; j < i - 1; j++ ) {
                (*out)[dec_len++] = a3[j];
            }
        }

        return (dec_len == out->size());
    }


    static unsigned long DecodedLength( const std::string &in ) {
        int numEq = 0;
        unsigned long n = in.size();

        for ( std::string::const_reverse_iterator it = in.rbegin(); *it == '='; ++it ) {
            ++numEq;
        }

        return ((6 * n) / 8) - numEq;
    }

    inline static size_t EncodedLength( size_t length ) {
        return (length + 2 - ((length + 2) % 3)) / 3 * 4;
    }

    inline static size_t EncodedLength( const std::string &in ) {
        return EncodedLength(in.length());
    }

    inline static void StripPadding( std::string *in ) {
        while ( !in->empty() && *(in->rbegin()) == '=' ) { in->resize(in->size() - 1); }
    }

private:
    static inline void a3_to_a4( unsigned char *a4, unsigned char *a3 ) {
        a4[0] = (a3[0] & 0xfc) >> 2;
        a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
        a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
        a4[3] = (a3[2] & 0x3f);
    }

    static inline void a4_to_a3( unsigned char *a3, unsigned char *a4 ) {
        a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
        a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
        a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
    }

    static inline unsigned char b64_lookup( unsigned char c ) {
        if ( c >= 'A' && c <= 'Z' ) { return c - 'A'; }
        if ( c >= 'a' && c <= 'z' ) { return c - 71; }
        if ( c >= '0' && c <= '9' ) { return c + 4; }
        if ( c == '+' ) { return 62; }
        if ( c == '/' ) { return 63; }
        return 255;
    }
};


#endif // BASE64_H
