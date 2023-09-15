#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main(void)
{
    int iResult;
    WSADATA wsaData;
    sockaddr_in client;

    // Starting Windows Socket API
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        wprintf(L"%d\n", WSAGetLastError());
        return 1;
    }

    // Creates and initalize a socckaddr_in struct with IPv4, PORT and Address
    client.sin_family = AF_INET;
    client.sin_port = htons(9090);
    inet_pton(AF_INET, "127.0.0.1", &client.sin_addr);

    std::cout << "Initialised " << std::endl;
    // Initialise socket for connection
    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == SOCKET_ERROR)
    {
        wprintf(L"%ld\n", WSAGetLastError());
        WSACleanup();
    }

    // To Connect with Server
    if (connect(connectSocket, (struct sockaddr *)&client, sizeof(client)) == SOCKET_ERROR)
    {
        wprintf(L"%ld\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
    }
    else
    {
        std::cout << "Connected" << std::endl;
    }

    return 0;
}