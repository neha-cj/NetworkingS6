#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void main(){
    int clientfd;
    struct sockaddr_in server_addr;
    char buffer[1024]="Hello from client";
    
    clientfd=socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(8080);

    connect(clientfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    send(clientfd,buffer,strlen(buffer),0);
    read(clientfd,buffer,sizeof(buffer));
    printf("response from client:%s\n",buffer);
    close(clientfd);

}