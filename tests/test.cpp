#include "test.h"

namespace fs = std::experimental::filesystem;

using namespace std;
using namespace Ljus;

TEST_CASE("encryption can be performed", "[crypt]") {
    string foo = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffoooooooooooooooooooooooooooo";

    string enc = Crypt::encrypt(foo);
    string dec = Crypt::decrypt(enc);
    REQUIRE(foo == dec);
}

TEST_CASE("hashes can be computed and checked", "[hash]") {
    string passwd = "password";
    string result = Hash::make(passwd);
    REQUIRE(Hash::check(passwd, result));
}

TEST_CASE("hashes status can be checked", "[hash]") {
    string passwd = "password";
    string result = Hash::make(passwd);
    SECTION("valid hash") {
        REQUIRE(!Hash::needs_rehash(result));
    }
    SECTION("invalid hash") {
        result.replace(result.find(",t=4"), 4, ",t=7");
        REQUIRE(Hash::needs_rehash(result));
    }
}

TEST_CASE("files can be created", "[filesystem]") {
    string content = "Hi I'm a nice file\n";
    int random = (rand() / 10000);
    string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    REQUIRE(Filesystem::exists(file));
    SECTION("gets chmod of 777") {
        Filesystem::chmod(file, fs::perms::group_read);
        REQUIRE((Filesystem::chmod(file) & fs::perms::group_read) != fs::perms::none);
        REQUIRE((Filesystem::chmod(file) & fs::perms::others_exec) == fs::perms::none);
    }
}
