#include "config.h"

#include <winsock2.h>
#include <windows.h>
#include <shlobj.h>
#include <string>
#include "../../httplib.h"

struct Login {
    bool Valid;
    std::string Server;
    std::string User;
};

Login retrieve_login(HINSTANCE hInstance);