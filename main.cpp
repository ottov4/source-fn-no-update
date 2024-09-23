#include "includes.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>
#include "auth/keyauth.hpp"
#include "security/skCrypt.hpp"
#include "Windows.h"
#include "bytes.h"

std::string name = skCrypt("Saturn Public").decrypt();
std::string ownerid = skCrypt("RRMW917rnj").decrypt();
std::string secret = skCrypt("235f27eb51b07480fdcdd8ade22669c0efe16dae212461c19519470543292f7a").decrypt();
std::string version = skCrypt("1.0").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt();
std::string path = skCrypt("payson1337").decrypt();

KeyAuth::api KeyAuthApp(name, ownerid, secret, version, url, path);

bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
    std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);

    if (!file_ofstream.write(address, size))
    {
        file_ofstream.close();
        return false;
    }

    file_ofstream.close();
    return true;
}

void load_drv()
{
    system("cls");
    system("color 6");
    auto drv = ("C:\\Windows\\System32\\dr.sys");
    auto mp = ("C:\\Windows\\System32\\mp.exe");

    CreateFileFromMemory(drv, reinterpret_cast<const char*>(driver_bytes), sizeof(driver_bytes));
    CreateFileFromMemory(mp, reinterpret_cast<const char*>(mapper), sizeof(mapper));

    system(("C:\\Windows\\System32\\mp.exe C:\\Windows\\System32\\dr.sys"));

    remove(("C:\\Windows\\System32\\dr.sys"));
    remove(("C:\\Windows\\System32\\mp.exe"));
}

int main()
{
    KeyAuthApp.init();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hConsole, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 600, 400, TRUE);
    SetConsoleTitleA(skCrypt("Payson Public - Made By github.com/paysonism").decrypt());

    system("color 5");
    std::cout << skCrypt("\n Payson Public - Made By Payson").decrypt();

    Sleep(3000);
    system("cls");

    std::cout << "\n Payson Public - discord.gg/saturniv\n\n Key > ";
    std::string key;
    std::cin >> key;
    KeyAuthApp.license(key);

   if (KeyAuthApp.response.success)
   {
        Sleep(3000);
        system("cls");
        std::cout << "\n Would you like to load the cheat driver? (y/n): ";
        std::string option;
        std::cin >> option;
        if (option == "Y" || option == "y")
        {
            load_drv();
        }
        if (option == "N" || option == "n")
        {
            Sleep(2000);
        }
        system("cls");
        system("color E");
        std::cout << skCrypt("\n [+] Launch Fortnite...").decrypt();
        while (game_wnd == 0)
        {
            Sleep(1);
            PaysonDRV::ProcessID = PaysonDRV::FindProcessID(L"FortniteClient-Win64-Shipping.exe");
            game_wnd = get_process_wnd(PaysonDRV::ProcessID);
            Sleep(1);
        }
        system(skCrypt("cls").decrypt());

        if (!librarys::init())
        {
            std::cout << skCrypt("\n Failed to initialize libraries.").decrypt();
            Sleep(3000);
            exit(0);
        }

        if (!input::init())
        {
            std::cout << skCrypt("\n Failed to initialize input libraries.").decrypt();
            Sleep(3000);
            exit(0);
        }

        if (!gui::init())
        {
            std::cout << skCrypt("\n Failed to initialize ImGui.").decrypt();
            Sleep(3000);
            exit(0);
        }

        if (!PaysonDRV::DriverInit())
        {
            std::cout << skCrypt("\n Driver not found. Please reload the driver and try again.").decrypt();
            Sleep(3000);
            exit(0);
        }

        virtualaddy = PaysonDRV::GetBaseAddress();
        if (!virtualaddy)
        {
            std::cout << skCrypt("\n Failed to get base address. Please contact support.").decrypt();
            Sleep(3000);
            exit(0);
        }
        system("color 5");
        std::cout << skCrypt("\n Base Address > ").decrypt() << virtualaddy << "\n";

        create_overlay();
        directx_init();
        render_loop();
   }
   else
   {
       system("cls");
       system("color 4");
       std::cout << "\n Incorrect Key.\n\n discord.gg/saturniv";
   }
}