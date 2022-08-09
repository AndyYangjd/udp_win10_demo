#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <windows.h>
#include <inaddr.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main(){
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0){
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2){
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }else{
        printf("The Winsock 2.2 dll was found okay\n");
    }

    SOCKET sockSrv = socket(AF_INET,SOCK_DGRAM, 0);
    if( sockSrv == INVALID_SOCKET ){
        printf("socket() fail:%d\n",WSAGetLastError());
        return -2;
    }

    SOCKADDR_IN  addrServ;
    memset(&addrServ,0,sizeof(addrServ));
    addrServ.sin_family = AF_INET;
    addrServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrServ.sin_port = htons(5556);

    err = bind(sockSrv,(SOCKADDR*)&addrServ,sizeof(SOCKADDR));
    if( err != 0 ){
        printf("bind()fail:%d\n",WSAGetLastError());
        return -3;
    }

    SOCKADDR_IN  addrClient;
    memset(&addrClient,0,sizeof(addrClient));
    int length = sizeof(SOCKADDR);
    char recvBuf[100];
    printf("waiting for client connect!!!!\n");
    recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&length);

    printf("recv from client:: %s\n",recvBuf);

    closesocket(sockSrv);

    WSACleanup();

    system("PAUSE");
    return 0;
}