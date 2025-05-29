#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "routes.h"
#include <iostream>
#include <fstream>
#include <filesystem>


int main() {

    httplib::SSLServer svr("certs/server.crt", "certs/server.key");

    if (!svr.is_valid()) {
        std::cerr << "Can't not access! Check your certificate" << std::endl;
        return 1;
    }

    setup_routes(svr);

    std::cout << "Success at https://localhost:443" << std::endl;
    svr.listen("0.0.0.0", 443);

    return 0;
}