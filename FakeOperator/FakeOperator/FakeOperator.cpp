// Make delay jitter between key presses
// Tidy up server client (most of it is stolen, also understand it...)
// Insert mouse wiggle
// Potentially create process checker to make sure process is running before typing

#define DEFAULT_BUFLEN 512


#include <ws2tcpip.h>
#include <tchar.h>

#include "KeyboardUtils.h"
#include "ExecuteCmds.h"
#include "WindowsUtils.h"
#include "Settings.h"
#include "KeyCodes.h"


using namespace KeyboardUtils;
using namespace WindowsUtils;

void ConnectToServer()
{
    std::string SHOST = "127.0.0.1";

    std::wstring stemp = std::wstring(SHOST.begin(), SHOST.end());
    LPCWSTR SHOST_LPC = stemp.c_str();

    WSADATA wsa_data;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &wsa_data);
    const auto server = socket(AF_INET, SOCK_STREAM, 0);

    InetPton(AF_INET, SHOST_LPC, &addr.sin_addr.s_addr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(6666);

    connect(server, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));
    printf("Connected to server!\n");

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive until the peer closes the connection
    int iResult;
    do {

        iResult = recv(server, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);
            std::string newCmd(recvbuf, iResult);
            ExecuteCommands::ParseCmd(newCmd);
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());

    } while (iResult > 0);


    closesocket(server);
    WSACleanup();
    printf("Socket closed\n");
        
}


int main()
{
   // GetDesktopResolution(horizontal, vertical);
    // Main loop for connecting to the server for cmds
    while (1)
    {
        ConnectToServer();
        Sleep(5000); // Testing 1
        //Sleep(CALL2SERVER); // Real
    
        //WindowFocus = get_window_title();
        //if (WindowFocus == "") std::cout << "Meh" << std::endl;
        //if (WindowFocus != "") std::cout << "I can type into -> " << WindowFocus << std::endl;


    }
    


}
