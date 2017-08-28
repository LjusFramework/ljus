#include "test.h"
#include "../ljus/hash/Hash.h"
#include "../ljus/encryption/Crypt.h"
#include <string.h>
#include <stdio.h>
using namespace std;

TEST_CASE("encryption can be performed", "[crypt]"){
    string foo = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffoooooooooooooooooooooooooooo";

    string enc = Crypt::make(foo);
    string dec = Crypt::decrypt(enc);
    REQUIRE(foo == dec);
}

TEST_CASE("hashes can be computed and checked", "[hash]"){
    string passwd1 = "password";
    string passwd2 = "";
    string passwd3 = "EXCEEDINGLY Lonadsg aspodfaisdgadsoigjeiowjtoeij jodfajsdokgjasokgjasodjf kjalsdkfjlaksdjf klkjklj\n";

    string passwd4 = string("password");

    string result1 = Hash::make(passwd1);
    int res = Hash::check(passwd1, result1);
    REQUIRE(res == 0);

    string result2 = Hash::make(passwd2);
    res = Hash::check(passwd2, result2);
    REQUIRE(res == 0);

    string result3 = Hash::make(passwd3);
    res = Hash::check(passwd3, result3);
    REQUIRE(res == 0);

    string result4 = string(Hash::make(passwd4.c_str()));
    res = Hash::check(passwd4.c_str(), result4.c_str());
    REQUIRE(res == 0);
}
