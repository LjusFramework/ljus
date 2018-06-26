#define CATCH_CONFIG_MAIN

#include "catch/catch.hpp"
#include "../ljus/hash/Hash.h"
#include "../ljus/encryption/Crypt.h"
#include "../ljus/files/Filesystem.h"
#include "../ljus/exceptions/NoSuchFileError.h"
#include "../ljus/view/View.h"
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <experimental/filesystem>
#include "../ljus/http/Route.h"
