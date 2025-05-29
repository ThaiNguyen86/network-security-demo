#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "routes.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// Hàm đọc nội dung file
std::string load_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "[ERROR] Cannot open file: " << path << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void setup_routes(httplib::SSLServer& svr) {
    // Route: GET /
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::string html = load_file("static/index.html");
        if (html.empty()) {
            res.status = 404;
            res.set_content("Index file not found", "text/plain");
        }
        else {
            res.set_content(html, "text/html");
        }
        });

    // Route: POST /login
    svr.Post("/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string user = req.get_param_value("username");
        std::string pass = req.get_param_value("password");
        if (user != "" && pass != "") {
            std::string html = load_file("static/welcome.html");
            res.set_content(html, "text/html");
        }
        else {
            res.set_content("Login failed!", "text/plain");
            res.status = 401;
        }

        });

    // Route: GET /static/*
    svr.Get(R"(/(.*))", [](const httplib::Request& req, httplib::Response& res) {
        std::string path = req.matches[1];
        std::string file_path = "static/" + path;

        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            res.status = 404;
            res.set_content("File not found", "text/plain");
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::string ext = fs::path(file_path).extension().string();

        std::string mime_type = "text/plain";
        if (ext == ".css") mime_type = "text/css";
        else if (ext == ".js") mime_type = "application/javascript";
        else if (ext == ".html") mime_type = "text/html";

        res.set_content(content, mime_type);
        });
}
