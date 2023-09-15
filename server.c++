#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main(void)
{
    WSADATA wsaData;

    int iResult;
    sockaddr_in server;

    // Initialise the windows socket API
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        wprintf(L"%ld \n", WSAGetLastError());
        return 1;
    }

    // Initialise the sockaddr_in struct with IPv4, PORT and Address
    server.sin_family = AF_INET;
    server.sin_port = htons(9090);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    SOCKET listenSocket = INVALID_SOCKET;

    // Initialize the socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
        wprintf(L"%ld\n", WSAGetLastError());
        WSACleanup();
    }

    // binds the socket to the server struct
    if (bind(listenSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        wprintf(L"%ld\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
    }
    std::cout << "[BINDED] server binded with socket" << std::endl;

    // listening
    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        wprintf(L"%ld\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
    }
    std::cout << "[LISTENING] socket is listening" << std::endl;

    SOCKET acceptSocket;

    while (true)
    {
        std::cout << "[ACCEPTING] waiting for client" << std::endl;
        acceptSocket = accept(listenSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET)
        {
            wprintf(L"%ld \n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
        }

        wprintf(L"%ld \n", WSAGetLastError());
        std::cout << "[CONNECTED] client connected" << std::endl;
    }

    closesocket(listenSocket);

    return 0;
}