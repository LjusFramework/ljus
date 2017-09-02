//
// Created by Erik Partridge on 24/08/17.
//

#include "Filesystem.h"

using namespace std;

bool Ljus::Filesystem::exists(const string& path) {
    return fs::exists(path);
}


string Ljus::Filesystem::get(const string& path){
    return fs::path(path).string();
}

//Returns a SHA-512 hash of the file contents
string Ljus::Filesystem::hash(const string& path){
    //TODO
    return path;
}

void Ljus::Filesystem::put(const string& path, const string& contents){

    ofstream file;

    file.open(path, ios::out);
    file << contents;

    file.close();

}

void Ljus::Filesystem::prepend(const string& path, const string& data){

    if(!Ljus::Filesystem::exists(path)){
        string original = Ljus::Filesystem::get(path);
        ofstream file;
        file.open(path, ios::out);
        file << original << data;
        file.close();
    } else {
        ofstream file;
        file.open(path, ios::out);
        file << data;
        file.close();
    }

}

void Ljus::Filesystem::append(const string& path, const string& data){
    ofstream file;
    file.open(path, ios::app);
    file << data;
    file.close();
}

fs::perms Ljus::Filesystem::chmod(const string& path){
    fs::path p(path);
    fs::file_status s = fs::status(p);
    return s.permissions();
}

void Ljus::Filesystem::chmod(const string& path, fs::perms perms){
    fs::permissions(fs::path(path), perms);
}

void Ljus::Filesystem::remove(const string& path){
    fs::remove(path);
}

void Ljus::Filesystem::remove(std::vector<string> paths){
    for (const auto &path : paths) {
        Ljus::Filesystem::remove(path);
    }
}

