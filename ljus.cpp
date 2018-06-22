#include "ljus.h"
#include "./external/http/http.h"

using namespace http;

#include <stdio.h>

int main() {

    //Pass to routes function
    Server server([](auto &req, auto &res) {
        for (auto elem : req.headers) {

            std::cout << elem.second << "\n";
        }
    });

    server.listen("0.0.0.0", 8000);
    return 0;
}
