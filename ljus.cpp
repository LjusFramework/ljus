#include "ljus.h"

using namespace Pistache;

int main() {



    Port port(6200);

    int threads = 1;
    if(const char* env_t = std::getenv("LJUS_ENV")){
        if(strcmp(env_t, "PRODUCTION") == 0){
            threads = 8;
        }
    }
    std::cout << "messg" << '\n';

    Address addr(Ipv4::any(), port);

    auto server = std::make_shared<Http::Endpoint>(addr);

    auto options = Http::Endpoint::options()
            .threads(threads);
    server->init(options);
    server->setHandler(Http::make_handler<LjusHandler>());
    server->serve();

    server->shutdown();
}
