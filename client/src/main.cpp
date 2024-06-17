#include "forscher.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Login login = retrieve_login(hInstance);
    
    if (!login.Valid) return 0;

    //string auth = get_auth(hInstance);
    //if (auth.empty()) return 0;

    

    return 0;
}