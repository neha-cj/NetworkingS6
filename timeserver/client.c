#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024] = "time";
    char response[1024];
    socklen_t len = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send request
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, len);
    printf("Time request sent to server\n");

    // Receive server's response
    memset(response, 0, sizeof(response));
    recvfrom(sockfd, response, sizeof(response), 0, (struct sockaddr *)&server, &len);
    printf("Server time: %s\n", response);

    close(sockfd);
    return 0;
}
