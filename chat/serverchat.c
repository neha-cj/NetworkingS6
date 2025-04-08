#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 1);
    
    printf("Waiting for connection...\n");
    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(newsock, buffer, sizeof(buffer));
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exited the chat.\n");
            break;
        }
        printf("Client: %s", buffer);

        memset(buffer, 0, sizeof(buffer));
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(newsock, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server exited the chat.\n");
            break;
        }
    }

    close(newsock);
    close(sockfd);
    return 0;
}
