#include "test.h"

namespace fs = std::experimental::filesystem;

using namespace std;
using namespace Ljus;


mt19937 rng(time(NULL));

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
    int random = (rng() / 10000);
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
    string content = "Hi I'm a nice file\n";
    int random = (rng() / 10000);
    string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    SECTION("gets a hash that can be recomputed"){
        REQUIRE(Filesystem::hash(file) == Filesystem::hash(file));
    }
}

TEST_CASE("files can be prepended", "[filesystem]"){
    string content = "1234567890";
    string content2 = "01234567890";
    int random = (rng() / 100000);
    string file = "/tmp/file-" + std::to_string(random);
    Filesystem::prepend(file, content);
    Filesystem::prepend(file, content2);
    REQUIRE(Filesystem::get(file) == content2 + content);

}

TEST_CASE("file system functions", "[filesystem]") {
    string content = "123456789";
    string content2 = "01234567890";
    int random = (rng() / 100000);
    string file = "/tmp/file-" + std::to_string(random);
    SECTION("appending can be performed", "[append]") {
        Filesystem::append(file, content);
        Filesystem::append(file, content2);
        REQUIRE(Filesystem::get(file) == (content + content2));
    }
    SECTION("sizing files", "[size]") {
        string file1 = "/tmp/file-" + std::to_string(random);
        Filesystem::put(file, content + content2);

        REQUIRE(Filesystem::size(file1) == 20);
    }
    Filesystem::copy(file, "/tmp/to-copy-to" + std::to_string(random));
    REQUIRE(Filesystem::size("/tmp/to-copy-to" + std::to_string(random)) == 20);
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
    REQUIRE(Filesystem::is_directory("/tmp"));
}

TEST_CASE("file modified time", "[filesystem]") {
    srand(time(NULL));
    int random = (rng() / 9000000);
    string file = "/tmp/file-a-" + std::to_string(random);
    Filesystem::put(file, "hi");
    REQUIRE((Filesystem::modified(file) <= time(NULL) && Filesystem::modified(file) > time(NULL) - 5000));
    REQUIRE(Filesystem::is_writable(file));
    REQUIRE(Filesystem::is_readable(file));
    Filesystem::chmod(file, fs::perms::none);
    REQUIRE(!Filesystem::is_writable(file));
    REQUIRE(!Filesystem::is_readable(file));
    Filesystem::chmod(file, fs::perms::all);
    Filesystem::remove(file);
}

TEST_CASE("file name processing", "[filesystem]") {
    string path = "/tmp/a-long-file.php";
    Filesystem::put(path, "Some php code");
    REQUIRE(Filesystem::is_file(path));
    REQUIRE(Filesystem::extension(path) == "php");
    string path2 = "/tmp/file.";
    Filesystem::put(path2, "random");
    REQUIRE(Filesystem::is_file(path2));
    REQUIRE(Filesystem::extension(path2) == "");
    REQUIRE(Filesystem::type(path2) == "file");
    REQUIRE(Filesystem::type("/tmp/") == "dir");
}

TEST_CASE("routing", "[route]") {
    Route::register_routes();
    try {
        auto action1 = Route::find("GET", "/");
        REQUIRE(action1 != nullptr);
    } catch ( int number ) {
        REQUIRE(number == 0);
    }


}