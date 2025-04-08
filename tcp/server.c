#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void main(){
    int sockfd, newsock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len =sizeof(client_addr);
    char buffer[1024]={0};

    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(8080);

   if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
    perror("bind failed\n");
    exit(0);
   }
   listen(sockfd,3);
   newsock=accept(sockfd,(struct sockaddr*)&client_addr,&len);
   read(newsock,buffer,sizeof(buffer));
   printf("message: %s",buffer);

   send(newsock,"Hello from Server",12,0);
   close(newsock);
   close(sockfd);
}