//
// Created by cents on 24/08/17.
//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <experimental/filesystem>
#include <vector>

#include <errno.h>
#include <sys/stat.h>

using namespace std;
namespace fs = std::experimental::filesystem;

namespace Ljus{
        
    class Filesystem {

    public:
        static bool exists(const string& path);
        static string get(const string& path);
        static string hash(const string& path);
        static void put(const string& path, const string& contents);
        static void prepend(const string& path, const string& data);
        static void append(const string& path, const string& data);
        static fs::perms chmod(const string& path);
        static void chmod(const string& path, fs::perms perms);
        static void remove(const string& path);
        static void remove(const vector<string> paths);
    };
}

#endif //FILESYSTEM_H
