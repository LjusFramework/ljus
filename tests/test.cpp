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
    srand(time(NULL));
    string content = "Hi I'm a nice file\n";
    int random = (rand() / 10000);
    string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    REQUIRE(Filesystem::exists(file));

    SECTION("Retrieves file as string"){
        REQUIRE(Filesystem::get(file) == content);
    }

    SECTION("gets chmod of 777") {
        Filesystem::chmod(file, fs::perms::group_read);
        REQUIRE((Filesystem::chmod(file) & fs::perms::group_read) != fs::perms::none);
        REQUIRE((Filesystem::chmod(file) & fs::perms::others_exec) == fs::perms::none);
    }
}

TEST_CASE("files can be hashed", "[filesystem"){
    srand(time(NULL));
    string content = "Hi I'm a nice file\n";
    int random = (rand() / 10000);
    string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    SECTION("gets a hash that can be recomputed"){
        REQUIRE(Filesystem::hash(file) == Filesystem::hash(file));
    }
}

TEST_CASE("files can be prepended", "[filesystem]"){
    srand(time(NULL));
    string content = "1234567890";
    string content2 = "01234567890";
    int random = (rand() / 100000);
    string file = "/tmp/file-" + std::to_string(random);
    Filesystem::prepend(file, content);
    Filesystem::prepend(file, content2);
    REQUIRE(Filesystem::get(file) == content2 + content);

}

TEST_CASE("file system functions", "[filesystem]") {
    string content = "1234567890";
    string content2 = "01234567890";
    int random = (rand() / 100000);
    string file = "/tmp/file-" + std::to_string(random);
    Filesystem::append(file, content);
    Filesystem::append(file, content2);
    REQUIRE(Filesystem::get(file) == (content + content2));
    REQUIRE(Filesystem::size(file) == 21);
    Filesystem::copy(file, "/tmp/to-copy-to" + std::to_string(random));
    REQUIRE(Filesystem::size("/tmp/to-copy-to" + std::to_string(random)) == 21);
    Filesystem::remove(file);
    try {
        Filesystem::get(file);
    } catch ( int x){
        REQUIRE (x != 0);
    }
    Filesystem::makeDirectory("/tmp/test_dir/");
    Filesystem::put("/tmp/test_dir/file", "Hello World");
    REQUIRE(Filesystem::files("/tmp/test_dir").size() == 1);
    Filesystem::remove(Filesystem::files("/tmp/test_dir"));
    REQUIRE(Filesystem::files("/tmp/test_dir").empty());
    REQUIRE(Filesystem::files("/tmp/randomtidirfasdtuhewruthaewitheihtiea").empty());
}

TEST_CASE("file modified time", "[filesystem]") {
    int random = (rand() / 9000000);
    string file = "/tmp/file-a-" + std::to_string(random);
    Filesystem::put(file, "hi");
    REQUIRE(Filesystem::modified(file) == time(NULL));

}