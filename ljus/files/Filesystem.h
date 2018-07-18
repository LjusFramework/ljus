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
#include "../exceptions/NoSuchFileError.h"
extern "C"{
        #include <blake2/blake2.h>
};

#include "../encryption/base64.h"

using string = std::string;

namespace fs = std::experimental::filesystem;

namespace Ljus {

    class Filesystem {

    public:
        /**
         * Check if a file exists
         * @param path the path to check
         * @return if the file exists
         */
        static bool exists( const string &path );

        /**
         * Get the size of a file in bytes
         * @param path the path of the file
         * @return the size of the file in bytes. Max value 2^127.
         */
        static long long size( const string &path );

        /**
         * Get the contents of a file as a string
         * @param path the path of the file
         * @return contents as a string
         */
        static string get( const string &path );

        /**
         * A secure hash of the file that can be used to check for file integrity
         * @param path the path of the file to digest
         * @return a string hash
         */
        static string hash( const string &path );

        /**
         * Put the provided contents at a given location, overwriting whatever was there previously.
         * @param path
         * @param contents
         */
        static void put( const string &path, const string &contents );

        /**
         * Prepend the contents at a given path
         * @param path the path of the file to prepend to
         * @param data the data that you wish to prepend
         */
        static void prepend( const string &path, const string &data );

        /**
         * Append the contents given to the file specified
         * @param path the path to the file
         * @param data the data which you wish to append
         */
        static void append( const string &path, const string &data );

        /**
         * Get the permissions of a given file
         * @param path the path of the file
         * @return the permission as a fs::perms object
         */
        static fs::perms chmod( const string &path );

        /**
         * Change permissions, similar to using chmod on unix operating systems
         * @param path the path of the file to impact the permissions
         * @param perms the permissions that you wish to aply
         */
        static void chmod( const string &path, fs::perms perms );

        /**
         * Delete a file at a given location.
         * @param path the path of the file
         */
        static void remove( const string &path );

        /**
         * Make a given directory
         * @param path the path of the directory to create
         */
        static void makeDirectory( const string &path );

        /**
         * Get a list of the files in a directory as paths
         * @param dir_path the path to the directory
         * @return paths to all the files in the directory
         */
        static std::vector<string> files( const string &dir_path );

        static void remove( std::vector<string> paths );

        static long long modified( const string &path );

        static void copy( const string &path, const string &target );

        static void move( const string &path, const string &target);

        static string name( const string &path );

        static string basename( const string &path );

        static string dirname( const string &path );

        static string extension( const string &path );

        static string type( const string &path );

        static string mime_type( const string &path );

        /**
         * Check if a given path is a directory
         * @param path the path of the potential directory
         * @return if it's a directory
         */
        static bool is_directory( const string &path );

        /**
         * Check if the user running this program has read access to the given file
         * @param path the path to the file you wish to check.`
         * @return
         */
        static bool is_readable( const string &path );

        /**
         * Check if the user running this program has write access to the given file
         * @param path the path to the file you wish to check.`
         * @return
         */
        static bool is_writable( const string &path );

        /**
         * Check if a given path is actually a file
         * @param path the path to the file
         * @return if it's a file!
         */
        static bool is_file( const string &path );

    private:
    };

}

#endif //FILESYSTEM_H
