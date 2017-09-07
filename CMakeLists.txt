cmake_minimum_required(VERSION 3.2.0)

project(LJUS C CXX)

# Set VERSION
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# If you want to fuzz turn this on
set(CMAKE_CXX_COMPILER /home/erik/Downloads/afl/afl-g++)
set(CMAKE_C_COMPILER /home/erik/Downloads/afl/afl-gcc)
# ---------------------------------------------------------------------
#                     COMPILE FLAGS
# ---------------------------------------------------------------------

option(debug "Use debugging flag" ON)
option(coverage "Use coverage flag" ON)

# C++ standard
# This will be by default C++17, adjust as needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

# Flags to always have on, some may be dropped, pthread cannot
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Set debug/coverage flags or optimize for production, depending on options.
if (debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    # Coverage dependent on -g
    # Don't optimize in debug
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    if (coverage)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif ()
else ()
    #Optimize for production, don't want fast math, others are fine
    SET(CMAKE_CXX_FLAGS "-O2")
endif ()

# -----------------------------------------------------------------------
#                            Locate files
# -----------------------------------------------------------------------

# Include everything
include_directories(
        ${PROJECT_SOURCE_DIR}/ljus
        ${PROJECT_SOURCE_DIR}/app
        ${PROJECT_SOURCE_DIR}/tests
        ${PROJECT_SOURCE_DIR}/external/pistache/include
        ${PROJECT_SOURCE_DIR}/external/argon2/include
        ${PROJECT_SOURCE_DIR}/external/json/src
        ${PROJECT_SOURCE_DIR}/other
        ${PROJECT_SOURCE_DIR}/external/argon2/src
)

link_directories(${CMAKE_SOURCE_DIR}/external)

# Get all the files from various components
file(GLOB HASH "ljus/hash/*.cpp")
file(GLOB CRYPT "ljus/encryption/*.cpp")
file(GLOB FILES "ljus/files/*.cpp")
file(GLOB HTTP "ljus/http/*.cpp")
file(GLOB CONFIG "config.cpp")
file(GLOB TEST "tests/*.cpp")
file(GLOB JSON "external/json/src/json.hpp")
file(GLOB BENCHMARK "other/benchmark/*.cpp")
file(GLOB B64 "ljus/encryption/base64.cpp")
file(GLOB PISTACHE_COMMON "external/pistache/src/common/*.cpp")
set(TEST_MAIN unit_tests.out)

# -----------------------------------------------------------------------
#                           Build
# -----------------------------------------------------------------------
add_library(hash ${HASH})
add_library(b64 ${B64})
add_library(crypt ${JSON} ${CRYPT})
add_dependencies(crypt b64)
add_dependencies(hash argon2)
target_link_libraries(crypt sodium)
target_link_libraries(crypt b64)
add_library(files ${FILES})
add_library(http ${HTTP})
add_dependencies(http pistache)
add_library(config ${CONFIG} ${JSON})

add_executable(app.out ljus.cpp ${JSON})

# Dependencies
add_dependencies(app.out pistache hash crypt files http config)
target_link_libraries(app.out pistache hash crypt files http config stdc++fs)

# ----------------------------------------------------------------------
#                       Building Pistache
# ----------------------------------------------------------------------
add_custom_target( git_update
        COMMAND git submodule init
        COMMAND git submodule update
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library( pistache
        ${PROJECT_SOURCE_DIR}/external/pistache/src/client/client.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/cookie.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/description.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/http.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/http_defs.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/http_header.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/http_headers.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/mime.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/net.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/os.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/peer.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/reactor.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/stream.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/tcp.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/timer_pool.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/common/transport.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/server/endpoint.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/server/listener.cc
        ${PROJECT_SOURCE_DIR}/external/pistache/src/server/router.cc )

add_dependencies(pistache git_update)

add_library( argon2
        ${PROJECT_SOURCE_DIR}/external/argon2/src/argon2.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/bench.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/encoding.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/core.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/genkat.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/opt.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/ref.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/run.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/test.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/thread.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/blake2/blake2b.c
        ${PROJECT_SOURCE_DIR}/external/argon2/src/blake2/blake2.h
        ${PROJECT_SOURCE_DIR}/external/argon2/src/blake2/blamka-round-opt.h
        ${PROJECT_SOURCE_DIR}/external/argon2/src/blake2/blamka-round-ref.h
        ${PROJECT_SOURCE_DIR}/external/argon2/src/blake2/blake2-impl.h
        ${PROJECT_SOURCE_DIR}/external/argon2/include/argon2.h
        )


# ----------------------------------------------------------------------
#                       Build test
# ----------------------------------------------------------------------
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)

add_executable(tests.out ${TEST_SOURCES})
add_dependencies(tests.out Catch pistache hash crypt files http config argon2)
target_link_libraries(tests.out Catch pistache hash crypt files http config stdc++fs argon2)

add_executable(fuzzhash other/fuzz_hash.cpp)
add_dependencies(fuzzhash hash)
target_link_libraries(fuzzhash hash argon2)

add_executable(sodiumfuzz other/sodium_fuzz.cpp other/sodium_fuzz.cpp other/sodium_fuzz.h)
target_link_libraries(sodiumfuzz sodium)
target_link_libraries(sodiumfuzz crypt)