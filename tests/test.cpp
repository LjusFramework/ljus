#include <http/BaseController.h>
#include "test.h"
#include "../external/json.hpp"

namespace fs = std::experimental::filesystem;

using namespace Ljus;


mt19937 rng(static_cast<unsigned int>(time(nullptr)));

TEST_CASE("encryption can be performed", "[crypt]") {
    std::string foo = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffoooooooooooooooooooooooooooo";
    std::string enc = Crypt::encrypt(foo);
    std::string dec = Crypt::decrypt(enc);
    REQUIRE(foo == dec);
}


TEST_CASE("hashes can be computed and checked", "[hash]") {
    std::string passwd = "password";
    std::string result = Hash::make(passwd);
    REQUIRE(Hash::check(passwd, result));
}


TEST_CASE("hashes status can be checked", "[hash]") {
    std::string passwd = "password";
    std::string result = Hash::make(passwd);
    SECTION("valid hash") {
        REQUIRE(!Hash::needs_rehash(result));
    }
}

TEST_CASE("files can be created", "[filesystem]") {
    std::string content = "Hi I'm a nice file\n";
    int random = (rng() / 10000);
    std::string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    REQUIRE(Filesystem::exists(file));

    SECTION("Retrieves file as string"){
        REQUIRE(Filesystem::get(file) == content);
    }
    SECTION("File contents are hashable and consistent"){
        REQUIRE(Filesystem::hash(file) == Filesystem::hash(file));
    }
    /*
    SECTION("gets chmod of 777") {
        Filesystem::chmod(file, fs::perms::group_read);
        REQUIRE((Filesystem::chmod(file) & fs::perms::group_read) != fs::perms::none);
        REQUIRE((Filesystem::chmod(file) & fs::perms::others_exec) == fs::perms::none);
    }*/
}

TEST_CASE("files can be hashed", "[filesystem"){
    std::string content = "Hi I'm a nice file\n";
    int random = (rng() / 10000);
    std::string file = "/tmp/" + std::to_string(random);
    Filesystem::put(file, content);
    SECTION("gets a hash that can be recomputed"){
        REQUIRE(Filesystem::hash(file) == Filesystem::hash(file));
    }
}


TEST_CASE("files can be prepended", "[filesystem]"){
    std::string content = "1234567890";
    std::string content2 = "01234567890";
    int random = (rng() / 100000);
    std::string file = "/tmp/file-" + std::to_string(random);
    Filesystem::prepend(file, content);
    Filesystem::prepend(file, content2);
    REQUIRE(Filesystem::get(file) == content2 + content);

}

TEST_CASE("file system functions", "[filesystem]") {
    std::string content = "123456789";
    std::string content2 = "01234567890";
    int random = (rng());
    std::string file = "/tmp/file-" + std::to_string(random);
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
    } catch (Ljus::Exceptions::NoSuchFileError &x){
        REQUIRE (true);
    }
    Filesystem::makeDirectory("/tmp/test_dir/");
    Filesystem::put("/tmp/test_dir/file", "Hello World");
    REQUIRE(Filesystem::files("/tmp/test_dir").size() == 1);
    Filesystem::remove(Filesystem::files("/tmp/test_dir"));
    REQUIRE(Filesystem::files("/tmp/test_dir").empty());
    REQUIRE(Filesystem::files("/tmp/randomtidirfasdtuhewruthaewitheihtiea").empty());
    REQUIRE(Filesystem::is_directory("/tmp"));
}
/*
TEST_CASE("file modified time", "[filesystem]") {
    srand(static_cast<unsigned int>(time(nullptr)));
    int random = (rng() % 9000000);
    std::string file = "/tmp/file-a-" + std::to_string(random);
    Filesystem::put(file, "hi");
    REQUIRE((Filesystem::modified(file) <= time(nullptr) && Filesystem::modified(file) > time(NULL) - 5000));
    REQUIRE(Filesystem::is_writable(file));
    REQUIRE(Filesystem::is_readable(file));
    Filesystem::chmod(file, fs::perms::none);
    REQUIRE(!Filesystem::is_writable(file));
    REQUIRE(!Filesystem::is_readable(file));
    Filesystem::chmod(file, fs::perms::all);
    Filesystem::remove(file);
}*/

TEST_CASE("file name processing", "[filesystem]") {
    std::string path = "/tmp/a-long-file.php";
    Filesystem::put(path, "Some php code");
    REQUIRE(Filesystem::is_file(path));
    REQUIRE(Filesystem::extension(path) == "php");
    std::string path2 = "/tmp/file.";
    Filesystem::put(path2, "random");
    REQUIRE(Filesystem::is_file(path2));
    REQUIRE(Filesystem::extension(path2).empty());
    REQUIRE(Filesystem::type(path2) == "file");
    REQUIRE(Filesystem::type("/tmp/") == "dir");
}


TEST_CASE("cache functions properly", "[cache]"){
    Store *store = new MemoryStore();
    SECTION("Put and retrieve") {
        store->forever("Hello", "World");
        REQUIRE(store->get("Hello") == "World");
    }
    SECTION("Forgetting works properly"){
        store->forget("Hello");
        REQUIRE(!store->has("Hello"));
    }
    SECTION("Incrementing") {
        store->forever("integer", "100");
        store->increment("integer", 1);
        REQUIRE(atoi(store->get("integer").c_str()) == 101);
    }
    SECTION("Existing and non-existent values") {
        REQUIRE(store->add("exists", "exists", 10));
        REQUIRE(!store->add("exists", "ex", 10));
        REQUIRE(store->forget("exists"));
    }
    SECTION("Testing the flushing procedure") {
        store->forever("Hello", "goodbye");
        store->flush();
        REQUIRE(!store->has("Hello"));
    }
    delete store;
}

TEST_CASE("rendering functions properly", "[view]"){
    RenderingEngine<kainjow::mustache::data> *engine = new MustacheEngine();
    std::string res = engine->render({"what", "World"}, "Hello {{what}}!");
    REQUIRE(res == "Hello World!");
    delete engine;
}

/*
TEST_CASE("routing", "[route]") {
    Route::register_routes();
    try {
        auto action1 = Route::find("GET", "/");
        REQUIRE(action1 != nullptr);
    } catch ( int number ) {
        REQUIRE(number == 0);
    }
    try {
        Route::put("/o", []( std::shared_ptr<Request> req, std::shared_ptr<Response> res ) -> Response {
            return BaseController().index(req, res);
        });
        auto res2 = Route::find("PUT", "/o");
        REQUIRE(res2 != nullptr);
    } catch ( int number ) {
        REQUIRE(number == 0);
    }
    try {
        Route::post("/o", []( std::shared_ptr<Request> req, std::shared_ptr<Response> res ) -> Response {
            return BaseController().index(req, res);
        });
        auto res3 = Route::find("POST", "/o");
        REQUIRE(res3 != nullptr);
    } catch ( int number ) {
        REQUIRE(number == 0);
    }

}*/