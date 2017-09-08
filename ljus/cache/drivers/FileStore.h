//
// Created by erik on 07/09/17.
//

#ifndef LJUS_FILEDRIVER_H
#define LJUS_FILEDRIVER_H

#include "../../files/Filesystem.h"
#include "../../../config.hpp"

using namespace Ljus;

namespace Ljus { namespace CacheDrivers {

    class FileDriver {

    public:
        std::string get(string key);
        void put(string key, string value, unsigned long long minutes);
        void forever(string key, string value);
        void forget( string key );
        bool flush();


    private:
        Filesystem filesystem = conf::file_driver;
        string folder;
        void ensureCacheDirectoryExists(string path);

    public:
        FileDriver(const Filesystem &filesystem, const string &folder);

        FileDriver();

        FileDriver(const string &folder);
    };
}}


#endif //LJUS_FILEDRIVER_H
