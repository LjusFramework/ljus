//
// Created by Erik A. Partridge on 6/26/18.
//

#ifndef LJUS_MEMORYSTORE_H
#define LJUS_MEMORYSTORE_H

#include "Store.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>      // std::invalid_argument

namespace Ljus {

    class MemoryStore : public Ljus::Store {
    public:
        std::string get(std::string key) override;

        void put(std::string key, std::string string, int minutes) override;

        bool has(std::string key) override;

        std::vector<std::string> many(std::vector<std::string> keys) override;

        bool add(std::string key, std::string value, int minutes) override;

        void increment(std::string key, long long value) override;

        bool forget(std::string key) override;

        bool flush() override;

    private:
        std::unordered_map<std::string, std::string> cache;
    };
}


#endif //LJUS_MEMORYSTORE_H
