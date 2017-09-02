#include "test.h"
#include "../ljus/hash/Hash.h"
#include "../ljus/encryption/Crypt.h"
#include <string.h>
#include <stdio.h>
using namespace std;
using namespace Ljus;

TEST_CASE("encryption can be performed", "[crypt]"){
    string foo = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffoooooooooooooooooooooooooooo";

    string enc = Crypt::encrypt(foo);
    string dec = Crypt::decrypt(enc);
    REQUIRE(foo == dec);
}

TEST_CASE("hashes can be computed and checked", "[hash]"){
    string passwd = "password";
    string result = Hash::make(passwd);
    REQUIRE(Hash::check(passwd, result));
}

TEST_CASE("hashes status can be checked", "[hash]"){
    string passwd = "password";
    string result = Hash::make(passwd);
    SECTION("valid hash"){
        REQUIRE(Hash::needs_rehash(result) == false);        
    }
    SECTION("invalid hash"){
        result.replace(result.find(",t=2"), 4, ",t=7");
        REQUIRE(Hash::needs_rehash(result) == true);    
    }
}
