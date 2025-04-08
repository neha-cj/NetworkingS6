#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void main(){
    int sockfd;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&client,&len);
    printf("response from client: %s",buffer);

    sendto(sockfd,"Hello from server",sizeof("Hello from server"),0,(struct sockaddr*)&client,len);
    close(sockfd);
}