/* Código do Servidor UDP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8081
#define BUFFER_SIZE 1024
#define END_MSG "END"  

int main() {

    WSADATA wsaData;
    int iResult;
    
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Falha ao iniciar o Winsock: %d\n", iResult);
        return 1;
    }

    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};
    FILE *file;

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Falha ao criar socket UDP: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Falha ao associar: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Servidor UDP aguardando pacotes...\n");

    file = fopen("received_udp.txt", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    int bytes_received;
    while (1) {
        bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received == SOCKET_ERROR) {
            printf("Erro ao receber dados: %d\n", WSAGetLastError());
            break;
        }

        if (strncmp(buffer, END_MSG, strlen(END_MSG)) == 0) {
            printf("Fim da transmissao recebido.\n");
            break;
        }

        fwrite(buffer, sizeof(char), bytes_received, file);
    }

    printf("Arquivo recebido e salvo como 'received_udp.txt'.\n");
    fclose(file);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
