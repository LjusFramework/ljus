#include <haywire.h>
#include "ljus.h"

int main() {


    char *root = "/";
    configuration config;
    config.http_listen_address = "127.0.0.1";
    config.http_listen_port = 8000;
    config.thread_count = 4;
    config.balancer = "ipc";
    config.parser = "http_parser";
    config.max_request_size = 2097576; // roughly 2 MiB
    config.tcp_nodelay = true;

    hw_init_with_config(&config);

    // Routing

    //
    hw_http_open();
    return 0;
}
