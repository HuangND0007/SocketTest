#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网卡

    bind(listenSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSock, 1);

    std::cout << "Server listening on 127.0.0.1:8080..." << std::endl;
    std::cout << "Waiting for client to connect (3-way handshake will happen here)..." << std::endl;

    struct sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    SOCKET clientSock = accept(listenSock, (struct sockaddr*)&clientAddr, &addrLen);

    std::cout << "Client connected! 3-way handshake completed." << std::endl;

    // 接收数据
    char buffer[1024];
    int received = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        std::cout << "Received from client: " << buffer << std::endl;
    }

    // 发送响应
    const char* response = "Hello from Server!";
    send(clientSock, response, (int)strlen(response), 0);

    std::cout << "Closing connection (4-way handshake)..." << std::endl;
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();

    return 0;
}
