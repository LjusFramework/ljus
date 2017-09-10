//
// Created by Erik Partridge on 24/08/17.
//

#include "Filesystem.h"

using namespace std;

/**
 * @brief Check if a file at a given path exists
 * @param path the path for which to check file existence
 * @return If the file exists
 */
bool Ljus::Filesystem::exists( const string &path ) {
    return fs::exists(fs::path(path));
}


string Ljus::Filesystem::get( const string &path ) {
    std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
    if ( in ) {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return contents.str();
    }
    throw (errno);
}

//Returns a SHA-512 hash of the file contents
string Ljus::Filesystem::hash( const string &path ) {
    return path;
}

void Ljus::Filesystem::put( const string &path, const string &contents ) {

    ofstream file;

    file.open(path, ios::out);
    file << contents;

    file.close();

}


void Ljus::Filesystem::prepend( const string &path, const string &data ) {

    if ( !Ljus::Filesystem::exists(path)) {
        put(path, data);
    } else {
        string contents = get(path);
        ofstream file;
        file.open(path, ios::out);
        file << data << contents;
        file.close();
    }

}

void Ljus::Filesystem::append( const string &path, const string &data ) {
    if ( exists(path)) {
        put(path, get(path) + data);
    } else {
        put(path, data);
    }
}

fs::perms Ljus::Filesystem::chmod( const string &path ) {
    fs::path p(path);
    fs::file_status s = fs::status(p);
    return s.permissions();
}

void Ljus::Filesystem::chmod( const string &path, fs::perms perms ) {
    fs::permissions(fs::path(path), perms);
}

void Ljus::Filesystem::remove( const string &path ) {
    fs::remove(path);
}

void Ljus::Filesystem::remove( std::vector<string> paths ) {
    for ( const auto &path : paths ) {
        Ljus::Filesystem::remove(path);
    }
}

void Ljus::Filesystem::makeDirectory( const string &path ) {
    fs::path p(path);
    fs::create_directories(p);
}

vector<string> Ljus::Filesystem::files( const string &dir_path ) {
    if ( not exists(dir_path)) {
        return vector<string>();
    }
    fs::path p(dir_path);

    vector<string> result;
    fs::directory_iterator end;
    for ( fs::directory_iterator i(dir_path); i != end; ++i ) {
        result.emplace_back(i->path().string());
    }
    return result;
}

/**
 * @brief Get the size of the file at the given path in bytes
 * @param path the path to the file
 * @return size of the file in bytes
 */
long long Ljus::Filesystem::size( const string &path ) {
    struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void Ljus::Filesystem::copy( const string &path, const string &target ) {
    fs::copy(fs::path(path), fs::path(target));
}

long long Ljus::Filesystem::modified( const string &path ) {
    struct stat result;
    int rc = stat(path.c_str(), &result);
    return rc == 0 ? result.st_mtim.tv_sec : -1;
}

bool Ljus::Filesystem::is_writable( const string &path ) {
    return access(path.c_str(), W_OK) == 0;
}

bool Ljus::Filesystem::is_readable( const string &path ) {
    return access(path.c_str(), R_OK) == 0;
}

bool Ljus::Filesystem::is_file( const string &path ) {
    struct stat result;
    int rc = stat(path.c_str(), &result);
    return result.st_mode & S_IFREG;
}

bool Ljus::Filesystem::is_directory( const string &path ) {
    struct stat result;
    int rc = stat(path.c_str(), &result);
    return result.st_mode & S_IFDIR;
}

string Ljus::Filesystem::extension( const string &path ) {
    size_t index = path.find_last_of('.');
    if ( index == string::npos || index == path.length() - 1 ) {
        return "";
    } else {
        return path.substr(index + 1);
    }
}


