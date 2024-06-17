#include "forscher.h"

LRESULT CALLBACK handle_login_prompt(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        // Check if the notification is from our button
        if (LOWORD(wParam) == 1)
        {
            DestroyWindow(handle);
        }
        break;
    case WM_CREATE:
    {
        LPCREATESTRUCT create = (LPCREATESTRUCT)lParam;
        Login *login = (Login *)(create->lpCreateParams);
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)login);

        CreateWindowEx(
            0, "EDIT",             // Predefined class
            login->Server.c_str(), // Default text
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            10, 10, 200, 24, // Position and dimensions
            handle,          // Parent window
            NULL,            // No menu
            (HINSTANCE)GetWindowLongPtr(handle, GWLP_HINSTANCE),
            NULL // Pointer not needed
        );

        CreateWindowEx(
            0, "Button", // Predefined class
            "einloggen", // Default text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 40, 200, 24, // Position and dimensions
            handle,          // Parent window
            (HMENU)1,        // No menu
            (HINSTANCE)GetWindowLongPtr(handle, GWLP_HINSTANCE),
            NULL // Pointer not needed
        );
    }
    break;
    case WM_CLOSE:
    {
        Login *login = (Login *)GetWindowLongPtr(handle, GWLP_USERDATA);
        login->Valid = false;
        DestroyWindow(handle);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }
    return 0;
}

void register_login_prompt(HINSTANCE hInstance)
{
    WNDCLASSEX prompt_class = {};

    prompt_class.cbSize = sizeof(WNDCLASSEX);
    prompt_class.style = 0;
    prompt_class.lpfnWndProc = handle_login_prompt;
    prompt_class.cbClsExtra = 0;
    prompt_class.cbWndExtra = 0;
    prompt_class.hInstance = hInstance;
    prompt_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    prompt_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    prompt_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    prompt_class.lpszMenuName = NULL;
    prompt_class.lpszClassName = "FORSCHER-LOGIN";
    prompt_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&prompt_class);
}

void prompt_login(HINSTANCE hInstance, Login *login)
{
    MSG message;

    HWND handle = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "FORSCHER-LOGIN",
        "Login - Heimatforscher",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        GetSystemMetrics(SM_CXSCREEN) / 2 - 200,
        GetSystemMetrics(SM_CYSCREEN) / 2 - 100,
        400, 200,
        NULL, NULL, hInstance, login);

    if (handle == NULL)
    {
        login->Valid = false;
        return;
    }

    ShowWindow(handle, SW_NORMAL);
    UpdateWindow(handle);

    while (GetMessage(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return;
}

std::string get_appdata_path()
{
    char base_appdata_path[MAX_PATH];
    std::string appdata_path;

    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, base_appdata_path)))
    {
        return std::string(base_appdata_path) + "\\" + STORAGE_DIRECTORY_NAME;
    }
    else
        return "";
}

Login *read_stored_login()
{
    Login *login = new Login();
    std::string appdata_path = get_appdata_path();
    std::string server;
    std::string user;

    if (appdata_path.empty())
    {
        MessageBox(NULL, "Zugriff auf lokale Dateien verweigert.", "Heimatforscher", MB_ICONERROR | MB_OK);

        login->Valid = false;
        return login;
    }

    std::ifstream server_file(appdata_path + "\\" + STORAGE_SERVER_FILE_NAME);
    std::ifstream user_file(appdata_path + STORAGE_USER_FILE_NAME);
    char read;

    server_file >> std::noskipws;
    user_file >> std::noskipws;

    while (server_file >> read)
        server += read;
    while (user_file >> read)
        user += read;

    if (server == "")
        server = DEFAULT_SERVER_DOMAIN;

    login->Valid = true;
    login->Server = server;
    login->User = user;
    return login;
}

void write_stored_login(Login *login)
{
    std::string appdata_path = get_appdata_path();

    if (appdata_path.empty())
        return;

    std::ofstream server_file(appdata_path + "\\" + STORAGE_SERVER_FILE_NAME);
    std::ofstream user_file(appdata_path + STORAGE_USER_FILE_NAME);

    for (int i = 0; i < login->Server.length(); ++i)
        server_file << login->Server[i];

    for (int i = 0; i < login->User.length(); ++i)
        user_file << login->User[i];
}

bool check_login(Login *login)
{
    httplib::Client client(login->Server);

    httplib::Headers headers;
    headers.emplace(REQUEST_USER_HEADER, login->User);

    auto response = client.Get("/", headers);

    return (response && response->status == 200);
}

Login retrieve_login(HINSTANCE hInstance)
{
    Login *login = read_stored_login();
    if (!login->Valid)
        return *login;

    register_login_prompt(hInstance);
    while (!check_login(login))
    {
        prompt_login(hInstance, login);

        if (!login->Valid)
            return *login;
    }

    write_stored_login(login);

    return *login;
}