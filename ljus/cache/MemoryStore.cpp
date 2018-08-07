//
// Created by Erik A. Partridge on 6/26/18.
//

#include "MemoryStore.h"

std::string Ljus::MemoryStore::get(std::string key) {
    return this->cache.at(this->get_prefix() + key);
}

void Ljus::MemoryStore::put(std::string key, std::string value, int minutes) {
    this->forget(key);
    this->cache.emplace(this->get_prefix() + key, value);
}

bool Ljus::MemoryStore::add(std::string key, std::string value, int minutes) {
    bool empty = this->cache.count(this->get_prefix() + key) == 0;
    if (empty){
        this->put(this->get_prefix() + key, value, minutes);
        return true;
    } else{
        return false;
        // Do nothing
    }
}

void Ljus::MemoryStore::putMany(std::vector<std::string> keys, std::vector<std::string> values, int minutes) {
    for(unsigned long i = 0; i < keys.size(); i ++ ){
        add(keys.at(i), values.at(i), minutes);
    }
};

void Ljus::MemoryStore::increment(std::string key, long long value) {
    std::string v = this->get(this->get_prefix() + key);
    try {
        long long val = atoll(v.c_str());
        val += value;
        this->forget(this->get_prefix() + key);
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
    std::vector<std::string> values;
    values.reserve(keys.size());
    for(const auto& key : keys){
        values.push_back(get(key));
    }
    return values;
}

bool Ljus::MemoryStore::has(std::string key) {
    return this->cache.count(this->get_prefix() + key) != 0;
}

void Ljus::MemoryStore::decrement(std::string key, long long value)
{
    Store::decrement(key, value);
}
void Ljus::MemoryStore::forever(std::string key, std::string value)
{
    Store::forever(key, value);
}
std::string Ljus::MemoryStore::get_prefix()
{
    return Store::get_prefix();
}

void Ljus::MemoryStore::set_prefix(std::string prefix)
{
    Store::set_prefix(prefix);
}
