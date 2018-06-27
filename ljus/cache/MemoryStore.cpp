//
// Created by Erik A. Partridge on 6/26/18.
//

#include "MemoryStore.h"

std::string Ljus::MemoryStore::get(std::string key) {
    return this->cache.at(this->get_prefix() + key);
}

void Ljus::MemoryStore::put(std::string key, std::string value, int minutes) {
    this->cache.emplace(this->get_prefix() + key, value);
}

bool Ljus::MemoryStore::add(std::string key, std::string value, int minutes) {
    bool empty = this->cache.count(this->get_prefix() + key) == 0;
    if (empty){
        this->put(this->get_prefix() + key, value, minutes);
    } else{
        // Do nothing
    }
    return !empty;
}

void Ljus::MemoryStore::increment(std::string key, long long value) {
    std::string v = this->get(this->get_prefix() + key);
    try {
        long long val = std::stoll(v, nullptr);
        val += value;
        this->forever(this->get_prefix() + key, std::to_string(val));
    } catch (std::invalid_argument &e){
        // Probably should do something more here
        //
    }
}

bool Ljus::MemoryStore::forget(std::string key) {
    if (this->cache.count(this->get_prefix() + key) != 0){
        this->cache.erase(this->get_prefix() + key);
        return true;
    } else {
        return false;
    }
}

bool Ljus::MemoryStore::flush() {
    this->cache = std::unordered_map<std::string, std::string>();
    return true;
}

std::vector<std::string> Ljus::MemoryStore::many(std::vector<std::string> keys) {
    return std::vector<std::string>();
}

bool Ljus::MemoryStore::has(std::string key) {
    return this->cache.count(this->get_prefix() + key) != 0;
}
