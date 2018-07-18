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

/**
 * @brief Get the contents of the file at a given path
 * @param path the path for whicih to get the file
 * @return the contents of the file
 */
string Ljus::Filesystem::get( const string &path ) {
    std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
    if ( in ) {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return contents.str();
    } else {
        throw Ljus::Exceptions::NoSuchFileError();
    }
}

/**
 * @brief Get the blake2b of the file contents
 * @param path the path of the file to compute the hash for
 * @return the blake2b hash of the file
 */
string Ljus::Filesystem::hash( const string &path ) {
    char encoded[64];
    std::string contents = Filesystem::get(path);
    blake2b_long(encoded, 64, contents.c_str(), contents.length());
    std::string res = encoded;
    std::string result;
    Base64::Encode(res, &result);
    return result;
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
#ifdef __APPLE__
    return rc == 0 ? result.st_mtimespec.tv_sec : -1;
#else
    return rc == 0 ? result.st_mtim.tv_sec : -1;
#endif
}

bool Ljus::Filesystem::is_writable( const string &path ) {
    return access(path.c_str(), W_OK) == 0;
}

bool Ljus::Filesystem::is_readable( const string &path ) {
    return access(path.c_str(), R_OK) == 0;
}

bool Ljus::Filesystem::is_file( const string &path ) {
    struct stat result;
    stat(path.c_str(), &result);
    return static_cast<bool>(result.st_mode & S_IFREG);
}

bool Ljus::Filesystem::is_directory( const string &path ) {
    struct stat result;
    stat(path.c_str(), &result);
    return static_cast<bool>(result.st_mode & S_IFDIR);
}

string Ljus::Filesystem::extension( const string &path ) {
    size_t index = path.find_last_of('.');
    if ( index == string::npos || index == path.length() - 1 ) {
        return "";
    } else {
        return path.substr(index + 1);
    }
}

string Ljus::Filesystem::type( const string &path ) {
    struct stat result;
    lstat(path.c_str(), &result);
    if ( S_ISLNK((result.st_mode))) {
        return "link";
    }
    stat(path.c_str(), &result);
    switch ( result.st_mode & S_IFMT ) {
        case S_IFBLK:
            return "block";
        case S_IFCHR:
            return "char";
        case S_IFDIR:
            return "dir";
        case S_IFIFO:
            return "fifo";
        case S_IFREG:
            return "file";
        case S_IFSOCK:
            return "socket";
        default:
            return "unknown";
    }
}

void Ljus::Filesystem::move(const string &path, const string &target) {
    copy(path, target);
    remove(path);
}


