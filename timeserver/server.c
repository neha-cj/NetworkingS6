#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Time Server is running...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Receive client request
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &len);
        printf("Received request from client: %s\n", buffer);

        // Get current time
        time_t now = time(NULL);
        char *time_str = ctime(&now);

        // Send current time back to client
        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client, len);
    }

    close(sockfd);
    return 0;
}
