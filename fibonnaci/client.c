#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024]={0};
    socklen_t len = sizeof(server);

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);

    while(1){
        printf("enter a number \n or 0 to exit\n");
        scanf("%s",buffer);
        if(strcmp(buffer,"0")==0){
            break;
        }
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&server,sizeof(server));
        memset(buffer,0,sizeof(buffer));
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,&len);
        printf("server says: %s\n",buffer);
    }
    close(sockfd);
}