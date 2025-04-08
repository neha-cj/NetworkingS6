#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Connected to server.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(sockfd, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exited the chat.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        read(sockfd, buffer, sizeof(buffer));
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server exited the chat.\n");
            break;
        }
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
