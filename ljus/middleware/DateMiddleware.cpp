//
// Created by Erik A. Partridge on 7/19/18.
//

#include "DateMiddleware.h"

int Ljus::DateMiddleware::before(Ljus::Request &req, Ljus::Response &res)
{
    return 0;
}

std::string get_http_time(){
    std::time_t now= std::time(nullptr);
    std::tm* now_tm= std::gmtime(&now);
    char buf[42];
    std::strftime(buf, 42, "%a, %d %b %Y %X GMT", now_tm);

    return std::string(buf);
}

int Ljus::DateMiddleware::after(Ljus::Request& req, Ljus::Response& res)
{
    res.set_header("Date", get_http_time());
    return 0;
}
