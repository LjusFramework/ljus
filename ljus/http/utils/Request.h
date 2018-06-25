//
// Created by erik on 08/09/17.
//

#ifndef LJUS_REQUEST_H
#define LJUS_REQUEST_H

namespace Ljus {
    class Request {
    public:
        std::vector<Cookie> get_cookies();

    private:
        std::vector<Cookie> cookies;
    };
}

#endif //LJUS_REQUEST_H
