#include <string>
#include "httplib.h"
using namespace std;
using namespace httplib;

int main()
{
    Server server;

    server.Get("/", [](const Request &request, Response &response) {
        if (request.has_header("forscher"))
        {
            string auth = request.get_header_value("forscher");

            if (auth == "elias:passwort") return;
        }

        response.status = StatusCode::Unauthorized_401;
    });

    server.listen("0.0.0.0", 80);
}