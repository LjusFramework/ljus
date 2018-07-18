#include "ljus.h"

#define DOCUMENT_ROOT "./public"
#ifdef USE_IPV6
#define PORT "[::]:8080"
#else
#define PORT "8080"
#endif

int error_handler( struct mg_connection *conn, int status, const char *msg ){
    return 0;
}

int log_handler( const struct mg_connection *conn, const char *message ){
    return 0;
}

int handler(struct mg_connection *conn, void *cbdata){
    return 0;
}

int main() {
    struct mg_callbacks callbacks;
    struct mg_context *ctx;
    struct mg_server_ports ports[32];
    int port_cnt, n;
    int err = 0;
    callbacks.http_error = error_handler;
    callbacks.log_message = log_handler;

    const char* options[] = {
            "document_root",
            DOCUMENT_ROOT,
            "listening_ports",
            PORT,
            "request_timeout_ms",
            "10000",
            "error_log_file",
            "ljus_server.log",
    #ifdef USE_WEBSOCKET
                "websocket_timeout_ms",
                "3600000",
    #endif
    #ifdef USE_SSL
                "ssl_certificate",
                "../../resources/cert/server.pem",
                "ssl_protocol_version",
                "3",
                "ssl_cipher_list",
        #ifdef USE_SSL_DH
                    "ECDHE-RSA-AES256-GCM-SHA384:DES-CBC3-SHA:AES128-SHA:AES128-GCM-SHA256",
        #else
                    "DES-CBC3-SHA:AES128-SHA:AES128-GCM-SHA256",
        #endif
    #endif

    };
#ifdef USE_IPV6
    if (!mg_check_feature(8)) {
		fprintf(stderr,
		        "Error: Embedded example built with IPv6 support, "
		        "but civetweb library build without.\n");
		err = 1;
	}
#endif
#ifdef USE_WEBSOCKET
    if (!mg_check_feature(16)) {
		fprintf(stderr,
		        "Error: Embedded example built with websocket support, "
		        "but civetweb library build without.\n");
		err = 1;
	}
#endif
#ifdef USE_SSL
    if (!mg_check_feature(2)) {
        fprintf(stderr,
                "Error: Embedded example built with SSL support, "
                "but civetweb library build without.\n");
        err = 1;
    }
#endif
    if (err) {
        fprintf(stderr, "Cannot start CivetWeb - inconsistent build.\n");
        return EXIT_FAILURE;
    }

    /* Start CivetWeb web server */
    memset(&callbacks, 0, sizeof(callbacks));

    ctx = mg_start(&callbacks, nullptr, options);
    if (ctx == nullptr) {
        fprintf(stderr, "Cannot start CivetWeb - mg_start failed.\n");
        return EXIT_FAILURE;
    }
    mg_set_request_handler(ctx, "/*", handler, nullptr);
    memset(ports, 0, sizeof(ports));
    std::string port_string = std::string(PORT);
    std::cout << "Ljus server is running at at http://localhost:" << port_string.substr(port_string.length() - 4) << std::endl;
    bool exitNow = false;
    while (!exitNow) {
        sleep(1);
    }
    mg_stop(ctx);
    return 0;
}
