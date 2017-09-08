//
// Created by erik on 07/09/17.
//

#include "FileStore.h"

CacheDrivers::FileDriver::FileDriver( const Filesystem &filesystem, const string &folder ) : filesystem(filesystem),
                                                                                             folder(folder) {
    this->filesystem = filesystem;
    this->folder = folder;
}

CacheDrivers::FileDriver::FileDriver( const string &folder ) : folder(folder) {
    this->filesystem = conf::file_driver;
    this->folder = folder;
}

CacheDrivers::FileDriver::FileDriver() {
    this->filesystem = conf::file_driver;
    this->folder = "storage/cache";
}

void CacheDrivers::FileDriver::ensureCacheDirectoryExists( string path ) {
    if ( !this->filesystem.exists(path)) {
        this->filesystem.makeDirectory(path);
    }
}

bool CacheDrivers::FileDriver::flush() {
    vector<string> contents = this->filesystem.directory_contents(this->folder);
    for(unsigned long long i = 0; i < contents.size(); ++ i){
        string path = contents.at(i);
        this->filesystem.remove(path);
    }
    return true;
}
