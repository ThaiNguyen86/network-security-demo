#include <httplib.h>
#include "routes.h"
#include <string>

int main() {
    httplib::Server svr;
    setup_routes(svr); // Defined in routes.cpp
    std::cout << "Success at http://localhost:80" << std::endl;
    svr.listen("0.0.0.0", 80);
    return 0;
}