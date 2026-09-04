#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    std::cout << "Client: Connecting to 127.0.0.1:8080..." << std::endl;

    // 这里发生 TCP 三次握手 (SYN -> SYN-ACK -> ACK)
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Client: Connected! 3-way handshake done." << std::endl;

    // 发送数据
    const char* msg = "Hello from Client!";
    send(sock, msg, (int)strlen(msg), 0);
    std::cout << "Client: Message sent." << std::endl;

    // 接收响应
    char buffer[1024];
    int received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        std::cout << "Client: Received response: " << buffer << std::endl;
    }

    // 关闭连接 (四次挥手)
    closesocket(sock);
    WSACleanup();
    std::cout << "Client: Disconnected." << std::endl;

    return 0;
}
