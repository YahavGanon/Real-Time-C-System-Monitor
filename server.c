#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") 

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_size;
    char response[1024];

    // 1. Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // 2. Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // 3. Bind and Listen
    bind(server_socket, (struct sockaddr*)&server, sizeof(server));
    listen(server_socket, 3);

    printf("OS Monitor Server running on http://127.0.0.1:8080\n");
    printf("Waiting for connections...\n");

    client_size = sizeof(struct sockaddr_in);

    // 4. Main loop
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client, &client_size)) != INVALID_SOCKET) {

        // Receive the request (prevents connection abortion)
        char buffer[1024] = { 0 };
        recv(client_socket, buffer, sizeof(buffer), 0);

        // Read real-time RAM usage from the OS
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        int memLoad = (int)memInfo.dwMemoryLoad;

        //Showing precentage in console
        printf("Client connected. Current RAM Usage sent: %d%%\n", memLoad);

        // Prepare HTTP Response with CORS headers
        sprintf(response,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Connection: close\r\n"
            "\r\n"
            "{\"ram_usage\": %d}", memLoad);

        // Send and close
        send(client_socket, response, (int)strlen(response), 0);
        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}