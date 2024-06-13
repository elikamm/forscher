#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include "httplib.h"

int main() {
    httplib::Client cli("http://localhost");

    auto res = cli.Get("/");

    MessageBox(0, res->body.c_str(), "Heimatforscher", MB_OK);

    return 0;
}