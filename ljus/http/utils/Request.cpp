
#include <iostream>
#include <cstring>
#include "Request.h"

std::vector<Ljus::Cookie> Ljus::Request::get_cookies() {
    return this->cookies;
}

std::vector<Ljus::Cookie> parse_cookies(const std::string& cookie_string){
    std::vector<std::string> split;
    std::string delimiter = "; ";
    char* pch = strtok(const_cast<char*>(cookie_string.c_str()), delimiter.c_str());
    while (pch != nullptr)
    {
        split.emplace_back(std::string(pch));
        pch = strtok (nullptr, delimiter.c_str());
    }

    std::vector<Ljus::Cookie> cookies;
    for (const auto& cookie_str : split){
        Ljus::Cookie cookie;
        unsigned long equals = cookie_str.find('=');
        cookie.name = cookie_str.substr(0, equals);
        cookie.value = cookie_str.substr(equals + 1,  cookie_str.length());
        cookies.emplace_back(cookie);
    }
    return cookies;
}

Ljus::Request::Request(struct mg_connection* conn)
{
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    std::string cookie_string = std::string(mg_get_header(conn, "Cookie"));
    std::string path = std::string(req_info->local_uri);
    std::map<std::string,std::string> headers;
    for(int i = 0; i < req_info->num_headers; i++){
        if (req_info->http_headers[i].value!= nullptr) {
            if (req_info->http_headers[i].name!=nullptr) {
                std::string name = std::string(req_info->http_headers[i].name);
                std::string value = std::string(req_info->http_headers[i].value);
                headers[name] = value;
            }
        }
    }
    if(req_info->query_string != nullptr){
        std::string query_string = std::string(req_info->query_string);
    } else {
        query_string = "";
    }
    auto secure = (bool)req_info->is_ssl;
    std::string user_ip = std::string(req_info->remote_addr);
    std::string method = std::string(req_info->request_method);

    std::vector<char> result;
    if(method != "GET") {
        char buffer[2048];
        int read_bytes = 1;
        while (read_bytes > 0) {
            read_bytes = mg_read(conn, buffer, sizeof(buffer));
            std::vector<char> temp(buffer, buffer + 2048);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        this->raw_content = result.data();
    }else {
        this->raw_content = std::string("").c_str();
    }
    this->content = std::string(raw_content);
    this->user_ip = user_ip;
    this->method = method;
    this->path = path;
    this->secure = secure;
    this->headers = headers;
    this->query_string = query_string;
    this->cookies = parse_cookies(cookie_string);

}
