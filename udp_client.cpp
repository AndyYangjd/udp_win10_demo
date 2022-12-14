#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")          //add ws2_32.lib

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }
    else
    {
        printf("The Winsock 2.2 dll was found okay\n");
    }


    SOCKET sockClient = socket(AF_INET,SOCK_DGRAM, 0);

    SOCKADDR_IN  addrServ;
    memset(&addrServ,0,sizeof(addrServ));
    addrServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(5556);
    printf("begin to send data to server\n");

    char strSend[1024] = {0};
    int id = 0;
    while(true){
        sprintf_s(strSend, "%d%f", 1, 3.1415f);
        printf("%zu\n", strlen(strSend)+1);
        auto ret = sendto(sockClient, strSend, strlen(strSend)+1, 0, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));
        if (ret <=0){
            printf("send fail: %d", WSAGetLastError());
        }else{
            id++;
            printf("send data(%d)\n", id);
        }
        Sleep(500);
    }

    closesocket(sockClient);

    system("PAUSE");
    WSACleanup();

    return 0;
}