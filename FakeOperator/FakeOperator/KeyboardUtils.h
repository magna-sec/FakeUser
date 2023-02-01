#pragma once // means header files are only compiled once... (dont delete this line again..)

#pragma comment(lib, "ws2_32")

#include <iostream>
#include <sys/types.h>
#include <winsock2.h>
#include <stdlib.h>

#include "WindowsUtils.h"
#include "Settings.h"

using namespace WindowsUtils;

namespace KeyboardUtils
{
    // Various Keys
    void ShiftKey(char key)
    {
        std::cout << "Shift + " << key << "\n\n";
        INPUT input[3] = {};
        HKL kbl = GetKeyboardLayout(0);

        // Shift Key - Down
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_LSHIFT;

        // Passed Key
        input[1].type = INPUT_KEYBOARD;
        input[1].ki.time = 0;
        input[1].ki.dwFlags = KEYEVENTF_UNICODE;

        //for lowercase
        if ((int)key < 65 || (int)key>90)
        {
            input[1].ki.wScan = 0;
            input[1].ki.wVk = VkKeyScanEx(key, kbl);
        }
        //for uppercase
        else
        {
            input[1].ki.wScan = key;
            input[1].ki.wVk = 0;

        }
        // Shift Key - Up
        input[2].type = INPUT_KEYBOARD;
        input[2].ki.wVk = VK_LSHIFT;
        input[2].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
        if (uSent != ARRAYSIZE(input))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void PressKey(char key)
    {
        int alter = rand() % 2; // 0 - 1
        // Speeds up and down typing
        if(alter == 0) Sleep(AVTIME / 2);
        if (alter == 1) Sleep(AVTIME * 2);

        INPUT input[1] = {};
        HKL kbl = GetKeyboardLayout(0);

        input[0].type = INPUT_KEYBOARD;
        input[0].ki.time = 0;
        input[0].ki.dwFlags = KEYEVENTF_UNICODE;

        //for lowercase
        if ((int)key < 65 || (int)key>90)
        {
            input[0].ki.wScan = 0;
            input[0].ki.wVk = VkKeyScanEx(key, kbl);
        }
        //for uppercase
        else
        {
            input[0].ki.wScan = key;
            input[0].ki.wVk = 0; 
        }

        input[0].ki.dwExtraInfo = 0;
        UINT uSent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
        if (uSent != ARRAYSIZE(input))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void PressEnter()
    {
        printf("Pressing Enter \n");
        Sleep(AVTIME);
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));

        // Enter Key - Down
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_RETURN;

        // Enter Key - Down
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_RETURN;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
        Sleep(LOADTIME);
    }
    void CtrlKey(char key)
    {
        std::cout << "Ctrl + " << key << "\n\n";

        INPUT inputs[4] = {};
        ZeroMemory(inputs, sizeof(inputs));

        /// CONTROL + Key
        // Control Key - Down
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_CONTROL;

        // Input Key - Down
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = key;

        // Control Key - Up
        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = VK_CONTROL;
        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

        // Input Key - Up
        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = key;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;


        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void WindowsShortcut(char key)
    {
        std::cout << "Windows + " << key << "\n\n";
        INPUT inputs[4] = {};
        ZeroMemory(inputs, sizeof(inputs));

        /// WINDOWS + Key
        // Window Key - Down
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LWIN;

        // Input Key - Down
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = key;

        // Windows Key - Up
        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = VK_LWIN;
        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

        // Input Key - Up
        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = key;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;


        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void PressTab()
    {
        printf("Pressing Tab\n");
        INPUT input[2] = {};
        HKL kbl = GetKeyboardLayout(0);

        // TAB Key - Down
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_TAB;


        // TAB Key - Up
        input[1].type = INPUT_KEYBOARD;
        input[1].ki.wVk = VK_TAB;
        input[1].ki.dwFlags = KEYEVENTF_KEYUP;


        UINT uSent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
        if (uSent != ARRAYSIZE(input))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void AltTab(int amount)
    {
        printf("Pressing Alt\n");
        INPUT input[2] = {};
        INPUT input2[1] = {};
        HKL kbl = GetKeyboardLayout(0);

        // Alt Key - Down
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_LMENU; //Mneu wtf? It's alt

    
        UINT uSent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
        std::cout << "Alt Down" << std::endl;

        if (uSent != ARRAYSIZE(input))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }

        // Tabbing 1 window at a time
        for (int a = 0; a <= amount; a++)
        {
            Sleep(1000);
            PressTab();
        }

        // Alt Key - Up
        input2[0].type = INPUT_KEYBOARD;
        input2[0].ki.wVk = VK_LMENU; //Mneu wtf? It's alt
        input2[0].ki.dwFlags = KEYEVENTF_KEYUP;


        UINT uSent2 = SendInput(ARRAYSIZE(input2), input2, sizeof(INPUT));
        std::cout << "Alt Up" << std::endl;
        if (uSent2 != ARRAYSIZE(input2))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
        PressEnter();

    }
    void TabToProcess(std::string name, std::string exe)
    {
        // If process we need is already running
        if (GetProcessIdByNameW(exe))
        {
            printf("I'll Tab then");
            // while current window isn't our process -> tab
            WindowFocus = get_window_title();

            int amount = 1;

            while (WindowFocus != name)
            {
                AltTab(amount);
                WindowFocus = get_window_title();
                amount++;
            }
            std::cout << "FOUND YA!" << std::endl;

        }
        else
        {
            printf("NAH MATE");
        }
    }

    void ArrowScroll()
    {

        int amount = rand() % 350; // 0 - 349
        int direction = amount % 2; // 0 - 1
        std::string directionstring = "";
        if (direction == 0)
            directionstring = " up ";
        else
            directionstring = " down ";
        std::cout << "\nScrolling " << amount << " times" << directionstring << "\n";


        INPUT inputs[350] = {};
        ZeroMemory(inputs, sizeof(inputs));

        for (int a = 0; a < amount; a++)
        {
            if (a % 2 == 1)
            {
                // Key - Down
                inputs[a].type = INPUT_KEYBOARD;
                if (direction == 1)
                    inputs[a].ki.wVk = VK_DOWN;
                else
                    inputs[a].ki.wVk = VK_UP;

            }
            else
            {
                // Key - Up
                inputs[a].type = INPUT_KEYBOARD;
                if (direction == 1)
                    inputs[a].ki.wVk = VK_DOWN;
                else
                    inputs[a].ki.wVk = VK_UP;
                inputs[a].ki.dwFlags = KEYEVENTF_KEYUP;
            }
        }

        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }
    }
    void KeyboardTyping(std::string text)
    {
        // Characters that you need shift to type
        std::string const SHIFTCHARS = "<>?:@~{}_+!£$%^&*()";
        // Interate over each character in std::string
        for (char& c : text) {
            if (SHIFTCHARS.find(c) < SHIFTCHARS.length())
            {
                ShiftKey(c);
            }
            else if (c == '#')
            {
                PressEnter();
            }
            else
            {
                PressKey(c);
            }
        }
    }
    void WindowsSearch(std::string searchword)
    {
        printf("Fake Keyboad Starting!\n");
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));

        /// WINDOWS 
        // Window Key - Down
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LWIN;

        // Windows Key - Up
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_LWIN;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;


        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            printf("SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
        }

        Sleep(LOADTIME);
        KeyboardTyping(searchword);
        PressEnter();
    }
}
