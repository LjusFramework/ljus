cmake_minimum_required(VERSION 3.4.0)

project(LJUS C CXX)

# Set VERSION
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# ---------------------------------------------------------------------
#                     COMPILE FLAGS
# ---------------------------------------------------------------------

option(debug "Use debugging flag" ON)
option(coverage "Use coverage flag" ON)

# C++ standard
# This will be by default C++17, adjust as needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

# Flags to always have on, some may be dropped, pthread cannot
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

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
        ${PROJECT_SOURCE_DIR}/external
        ${PROJECT_SOURCE_DIR}/other
)

# Get all the files from various components
file(GLOB HASH "ljus/hash/*.cpp")
file(GLOB CRYPT "ljus/encryption/*.cpp")
file(GLOB FILES "ljus/files/*.cpp")
file(GLOB HTTP "ljus/http/*.cpp")
file(GLOB CONFIG "config.cpp")
file(GLOB TEST "tests/*.cpp")
file(GLOB BENCHMARK "other/benchmark/*.cpp")

set(TEST_MAIN unit_tests.out)

# -----------------------------------------------------------------------
#                           Build
# -----------------------------------------------------------------------
add_library(hash ${HASH})
add_library(crypt ${CRYPT})
add_library(files ${FILES})
add_library(http ${HTTP})
add_library(config ${CONFIG})

add_executable(app.out ljus.cpp)

# Dependencies
add_dependencies(app.out hash crypt files http config)
target_link_libraries(app.out hash crypt files http config)




