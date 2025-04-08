#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024]={0};
    char response[1024]={0};

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("connected to server\n");
    while(1){
        memset(buffer,0,sizeof(buffer));
        printf("enter a string to reverse: ");
        scanf("%s",buffer);
        send(sockfd, buffer, strlen(buffer),0);
        read(sockfd, response, sizeof(response));
        printf("reversed string: %s\n",response);

    }
    close(sockfd);
}