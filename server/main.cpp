#include "httplib.h"

int main()
{
    httplib::Server server;

    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    server.listen("0.0.0.0", 80);
}