#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

void main(){
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("connected with server\n");
    while(1){
        memset(buffer,0,sizeof(buffer));
        printf("enter a number to check if amrstrong: \n");
        scanf("%s",buffer);
        send(sockfd,buffer,strlen(buffer),0);
        memset(buffer,0,sizeof(buffer));
        read(sockfd,buffer,sizeof(buffer));
        printf("server: %s\n",buffer);
    }
    close(sockfd);
    
}