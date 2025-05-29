#ifndef ROUTES_H
#define ROUTES_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

void setup_routes(httplib::SSLServer& svr);

#endif
