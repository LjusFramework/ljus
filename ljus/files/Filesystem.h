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
#include <unistd.h>
#include <cerrno>
#include <sys/stat.h>
#include "../../config.hpp"
#include "../exceptions/NoSuchFileError.h"

using string = std::string;

namespace fs = std::experimental::filesystem;

namespace Ljus {

    class Filesystem {

    public:

        static bool exists( const string &path );

        static long long size( const string &path );

        static string get( const string &path );

        static string hash( const string &path );

        static void put( const string &path, const string &contents );

        static void prepend( const string &path, const string &data );

        static void append( const string &path, const string &data );

        static fs::perms chmod( const string &path );

        static void chmod( const string &path, fs::perms perms );

        static void remove( const string &path );

        static void makeDirectory( const string &path );

        static std::vector<string> files( const string &dir_path );

        static void remove( std::vector<string> paths );

        static long long modified( const string &path );

        static void copy( const string &path, const string &target );

        static string name( const string &path );

        static string basename( const string &path );

        static string dirname( const string &path );

        static string extension( const string &path );

        static string type( const string &path );

        static string mime_type( const string &path );

        static bool is_directory( const string &path );

        static bool is_readable( const string &path );

        static bool is_writable( const string &path );

        static bool is_file( const string &path );

    private:
    };

}

#endif //FILESYSTEM_H
