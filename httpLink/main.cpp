#include "httplib.h"
#include <iostream>

int main() {
    // ========== 示例 1：简单的 GET 请求 ==========
    {
        httplib::Client cli("http://httpbin.org");

        std::cout << "=== GET 请求 ===" << std::endl;
        auto res = cli.Get("/get");

        if (res && res->status == 200) {
            std::cout << "状态码: " << res->status << std::endl;
            std::cout << "响应体:\n" << res->body << std::endl;
        } else {
            std::cout << "GET 请求失败" << std::endl;
        }
    }

    // ========== 示例 2：带参数的 GET ==========
    {
        httplib::Client cli("http://httpbin.org");

        std::cout << "\n=== 带参数的 GET ===" << std::endl;
        httplib::Params params{
            {"name", "Alice"},
            {"age", "25"}
        };
        auto res = cli.Get("/get", params);

        if (res && res->status == 200) {
            std::cout << res->body << std::endl;
        }
    }

    // ========== 示例 3：POST JSON ==========
    {
        httplib::Client cli("http://httpbin.org");

        std::cout << "\n=== POST JSON ===" << std::endl;
        httplib::Headers headers = {
            {"Content-Type", "application/json"}
        };
        std::string json_body = R"({"username":"test","password":"123456"})";

        auto res = cli.Post("/post", headers, json_body, "application/json");

        if (res && res->status == 200) {
            std::cout << "POST 成功:\n" << res->body << std::endl;
        } else {
            std::cout << "POST 失败" << std::endl;
        }
    }

    // ========== 示例 4：设置超时 ==========
    {
        httplib::Client cli("http://httpbin.org");
        cli.set_connection_timeout(5);  // 连接超时 5 秒
        cli.set_read_timeout(10);       // 读取超时 10 秒

        std::cout << "\n=== 带超时的请求 ===" << std::endl;
        auto res = cli.Get("/delay/1");  // httpbin 会延迟 1 秒返回

        if (res && res->status == 200) {
            std::cout << "请求成功" << std::endl;
        }
    }

    return 0;
}
