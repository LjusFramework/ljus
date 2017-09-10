//
// Created by Erik Partridge on 24/08/17.
//

#include <cstring>
#include "Filesystem.h"
#include "../../config.hpp"

using namespace std;

bool Ljus::Filesystem::exists(const string &path) {
    return fs::exists(path);
}


string Ljus::Filesystem::get(const string &path) {
    std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
    if (in){
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return contents.str();
    }
    throw(errno);
}

//Returns a SHA-512 hash of the file contents
string Ljus::Filesystem::hash(const string &path) {
//TODO
    return string(reinterpret_cast<char *>(hash));
}

void Ljus::Filesystem::put(const string &path, const string &contents) {

    ofstream file;

    file.open(path, ios::out);
    file << contents;

    file.close();

}


void Ljus::Filesystem::prepend(const string &path, const string &data) {

    if (!Ljus::Filesystem::exists(path)) {
        put(path, data);
    } else {
        string contents = get(path);
        ofstream file;
        file.open(path, ios::out);
        file << data << contents;
        file.close();
    }

}

void Ljus::Filesystem::append(const string &path, const string &data) {
    ofstream file;
    file.open(path, ios::app);
    file << data;
    file.close();
}

fs::perms Ljus::Filesystem::chmod(const string &path) {
    fs::path p(path);
    fs::file_status s = fs::status(p);
    return s.permissions();
}

void Ljus::Filesystem::chmod(const string &path, fs::perms perms) {
    fs::permissions(fs::path(path), perms);
}

void Ljus::Filesystem::remove(const string &path) {
    fs::remove(path);
}

void Ljus::Filesystem::remove(std::vector<string> paths) {
    for (const auto &path : paths) {
        Ljus::Filesystem::remove(path);
    }
}

void Ljus::Filesystem::makeDirectory(const string &path) {
    fs::path p(path);
    fs::create_directories(p);
}

vector<string> Ljus::Filesystem::files( const string &dir_path ) {
    if(!exists(dir_path)){
        return vector<string>();
    }
    fs::path p(dir_path);

    vector<string> result;
    fs::directory_iterator end;
    for(fs::directory_iterator i(dir_path); i != end; ++i){
        result.emplace_back(i->path().string());
    }
    return result;
}

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


