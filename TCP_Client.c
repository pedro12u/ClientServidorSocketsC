/* Código do Cliente TCP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Falha ao iniciar o Winsock: %d\n", iResult);
        return 1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    FILE *file = fopen("file_to_send.txt", "rb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        WSACleanup();
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro na criaçao do socket: %d\n", WSAGetLastError());
        fclose(file);
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        printf("Endereco invalido\n");
        fclose(file);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Conexao falhou: %d\n", WSAGetLastError());
        fclose(file);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Conectado ao servidor. Enviando arquivo...\n");

    int bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    printf("Arquivo enviado ao servidor.\n");
    fclose(file);
    closesocket(sock);
    WSACleanup();
    return 0;
}
