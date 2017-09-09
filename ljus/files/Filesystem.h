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

#include <cerrno>
#include <sys/stat.h>

using namespace std;
namespace fs = std::experimental::filesystem;

namespace Ljus{
        
    class Filesystem {

    public:
        Filesystem();

        static bool exists(const string& path);

        static long long size( const string &path );
        static string get(const string& path);
        static string hash(const string& path);
        static void put(const string& path, const string& contents);
        static void prepend(const string& path, const string& data);
        static void append(const string& path, const string& data);
        static fs::perms chmod(const string& path);
        static void chmod(const string& path, fs::perms perms);
        static void remove(const string& path);
        static void makeDirectory(const string& path);
        static vector<string> directory_contents( const string &dir_path );
        static void remove(vector<string> paths);

        static void copy( const string &path, const string &target );
    };
}

#endif //FILESYSTEM_H
