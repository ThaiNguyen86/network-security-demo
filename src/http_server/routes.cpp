#include "routes.h"
#include <filesystem>
#include <fstream>

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

void setup_routes(httplib::Server& svr) {
    // Route để phục vụ index.html
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::filesystem::path staticPath = std::filesystem::current_path().parent_path().parent_path() / "static" / "index.html";
        std::ifstream file(staticPath);
        if (file.is_open()) {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            res.set_content(content, "text/html");
        }
        else {
            res.set_content("File not found", "text/plain");
            res.status = 404; // Set status code separately
        }
        });

    // Route để phục vụ các file tĩnh (CSS, JS, v.v.)
    svr.Get("/(.*)", [](const httplib::Request& req, httplib::Response& res) {
        auto path = req.matches[1];
        std::filesystem::path staticPath = std::filesystem::current_path().parent_path().parent_path() / "static" / path.str();

        std::ifstream file(staticPath);
        if (file.is_open()) {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            std::string mime_type = "text/plain";
            if (staticPath.extension() == ".css") {
                mime_type = "text/css";
            }
            else if (staticPath.extension() == ".js") {
                mime_type = "application/javascript";
            }
            else if (staticPath.extension() == ".html") {
                mime_type = "text/html";
            }
            res.set_content(content, mime_type.c_str());
        }
        else {
            res.set_content("File not found", "text/plain");
            res.status = 404; // Set status code separately
        }
        });


    // Route xử lý đăng nhập
    svr.Post("/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string user = req.get_param_value("username");
        std::string pass = req.get_param_value("password");
        if (user != "" && pass != "") {
            std::string html = load_file("../../static/welcome.html");
            res.set_content(html, "text/html");
        }
        else {
            res.set_content("Login failed!", "text/plain");
            res.status = 401;
        }
        });
}