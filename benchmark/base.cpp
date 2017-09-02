#define BENCHPRESS_CONFIG_MAIN
#include "benchpress.hpp"
#include "../ljus/encryption/Crypt.h"
#include "../ljus/hash/Hash.h"
#include "../ljus/files/Filesystem.h"
#include <chrono>
#include <iostream>
#include <string>
#include "../includes/cppcodec/cppcodec/base64_rfc4648.hpp"
#include <experimental/filesystem>

using base64 = cppcodec::base64_rfc4648;
namespace fs = std::experimental::filesystem;

using namespace Ljus;

BENCHMARK("encryption", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::string res = Crypt::encrypt(std::string("some random content here "));
    }
});

BENCHMARK("hashing", [](benchpress::context* ctx) {
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::string res = Hash::make(std::string("some random content here "));
    }
});

BENCHMARK("get file contents", [](benchpress::context* ctx) {
    char salt[60000];    
    int fd = open("/dev/urandom", O_RDONLY);
    int size = read(fd, salt, 60000);
    close(fd);
    const std::string stringified = std::string(salt);
    base64::encode(stringified);
    Filesystem::put("/tmp/ljus-benchmark-file", stringified);
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::string res = Filesystem::get("/tmp/ljus-benchmark-file");
    }
});

BENCHMARK("get file contents", [](benchpress::context* ctx) {
    char salt[60000];    
    int fd = open("/dev/urandom", O_RDONLY);
    int size = read(fd, salt, 60000);
    close(fd);
    const std::string stringified = std::string(salt);
    base64::encode(stringified);
    Filesystem::put("/tmp/fs-benchmark-file", stringified);
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::string res = fs::path("/tmp/fs-benchmark-file").string();
    }
});
