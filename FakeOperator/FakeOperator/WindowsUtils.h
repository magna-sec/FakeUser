#pragma once


#include <tlhelp32.h>

#include "Settings.h"


namespace WindowsUtils 
{
    // READ -> FORMAT -> UNDERSTAND
    void GetDesktopResolution(int& horizontal, int& vertical)
    {
        RECT desktop;
        // Get a handle to the desktop window
        const HWND hDesktop = GetDesktopWindow();
        // Get the size of screen to the variable desktop
        GetWindowRect(hDesktop, &desktop);
        // The top left corner will have coordinates (0,0)
        // and the bottom right corner will have coordinates
        // (horizontal, vertical)
        horizontal = desktop.right;
        vertical = desktop.bottom;
    }


    std::string get_window_title()
    {
        HWND hwnd = GetForegroundWindow();
        wchar_t window_title[256];

        SendMessageW(hwnd, WM_GETTEXT, (WPARAM)256, (LPARAM)window_title);


        // Changing wchar_t to wstring to string, had problems with output
        std::wstring ws(window_title);
        // your new String
        std::string stringoutput(ws.begin(), ws.end());


        if (hwnd == InvalidValue)
        {
            CloseHandle(hwnd);
        }

        std::string program_list[4] = { "Word", "Firefox", "Chrome", "PowerShell.lnk" };
        short list_amount = std::size(program_list);

        short found = 0;


        while (stringoutput != "")
        {
            short length = stringoutput.length();

            std::string found_program = "";

            for (int i = 0; i < length; i++)
            {

                std::string b = stringoutput.substr(stringoutput.length() - i, stringoutput.length());

                for (int p = 0; p < list_amount; p++)
                {
                    if (b == program_list[p])
                    {
                        found = 1;
                        found_program = b;
                        break;
                    }
                    if (found) break;
                }
                if (found) break;

            }
            if (found) return found_program;
            break;
        }



        return "";

    }

    boolean GetProcessIdByNameW(std::string name)
    {
        // Mostly "stolen code"... edited to what I need
        PROCESSENTRY32 pe32;
        HANDLE snapshot = NULL;
        DWORD pid = 0;


        snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot != INVALID_HANDLE_VALUE)
        {
            pe32.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(snapshot, &pe32))
            {
                do
                {
                   // std::wcout << pe32.szExeFile << std::endl; // HANDY FOR FINDING Process EXEs

                    std::wstring tempname(pe32.szExeFile);
                    // your new String
                    std::string processname(tempname.begin(), tempname.end());

                    if (!strcmp(processname.c_str(), name.c_str()))
                    {
                        return true;
                        break;
                    }
                } while (Process32Next(snapshot, &pe32));
            }
            CloseHandle(snapshot);
        }
        return false;
    }

   


}