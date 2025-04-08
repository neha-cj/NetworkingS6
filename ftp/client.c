#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024], filename[100];
    FILE *fp;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Enter filename to download: ");
    scanf("%s", filename);

    send(sockfd, filename, strlen(filename), 0);

    fp = fopen("received_file.txt", "w");
    memset(buffer, 0, sizeof(buffer));
    int n;
    while ((n = read(sockfd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[n] = '\0';
        fputs(buffer, fp);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("File received and saved as 'received_file.txt'\n");
    fclose(fp);
    close(sockfd);
    return 0;
}
