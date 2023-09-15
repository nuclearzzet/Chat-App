#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

int main(int argc, char **argv)
{
    WSADATA wsaData;

    int iResult;
    struct sockaddr_in server;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult == ERROR)
    {
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
        wprintf(L"%d\n", WSAGetLastError());
        WSACleanup();
    }

    // binds the socket to the server struct
    if (bind(listenSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        wprintf(L"%d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
    }

    // listening
    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        wprintf(L"%d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
    }

    // calls accept function
    acceptSocketFunc(listenSocket, &server);

    return 0;
}

// TO accept Sockets
int acceptSocketFunc(SOCKET ls, struct sockaddr_in *s)
{
    SOCKET acceptSocket;

    acceptSocket = accept(ls, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        wprintf("%d\n", WSAGetLastError());
        closesocket(ls);
        WSACleanup();
    }

    wprintf(L"CLient connected\n");
    closesocket(ls);

    return 0;
}