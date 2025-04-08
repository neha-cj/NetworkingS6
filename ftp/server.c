#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    char buffer[1024];
    FILE *fp;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 1);
    printf("FTP Server waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Client connected.\n");

    memset(buffer, 0, sizeof(buffer));
    read(newsock, buffer, sizeof(buffer));  // Receive filename
    printf("Requested file: %s\n", buffer);

    fp = fopen(buffer, "r");
    if (fp == NULL) {
        char *msg = "ERROR: File not found.";
        send(newsock, msg, strlen(msg), 0);
    } else {
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            send(newsock, buffer, strlen(buffer), 0);
        }
        fclose(fp);
    }

    close(newsock);
    close(sockfd);
    return 0;
}
