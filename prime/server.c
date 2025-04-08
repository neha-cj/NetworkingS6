#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    char response[1024];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 1);
    printf("Waiting for client...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    printf("Client connected.\n");
    while(1){
    memset(buffer, 0, sizeof(buffer));
    read(newsock, buffer, sizeof(buffer));

    int num = atoi(buffer);
    printf("Received number: %d\n", num);

    if(is_prime(num)){
        strcpy(response,"Is Prime");
    }
    else{
        strcpy(response,"Not Prime");
    }
    send(newsock, response, strlen(response), 0);
}
    close(newsock);
    close(sockfd);
    return 0;
}
