//
// Created by Erik A. Partridge on 6/26/18.
//

#ifndef LJUS_STORE_H
#define LJUS_STORE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace Ljus {

    class Store {

        public:
            virtual ~Store() = default;
            virtual std::string get(std::string key)= 0;

            virtual bool has(std::string key) = 0;

            virtual void put(std::string key, std::string, int minutes) = 0;

            virtual std::vector<std::string> many(std::vector<std::string> keys) = 0;

            virtual void putMany(std::vector<std::string> keys, std::vector<std::string> values, int minutes) = 0;

            virtual bool add(std::string key, std::string value, int minutes) = 0;
            virtual void increment(std::string key, long long value) = 0;

            virtual void decrement(std::string key, long long value){
                increment(std::move(key), -1 * value);
            }

            virtual void forever(std::string key, std::string value){
                put(std::move(key), std::move(value), 2628000);
            }
           // virtual Lock(std::string name, int seconds);
            virtual bool forget(std::string key) = 0;
            virtual bool flush() = 0;
            virtual std::string get_prefix(){
                return prefix;
            }
            virtual void set_prefix(std::string prefix){
                this->prefix = std::move(prefix);
            }
    private:
        std::string prefix = "";
    };
}


#endif //LJUS_STORE_H
