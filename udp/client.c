#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void main(){
    int sockfd;
    char buffer[1024]="Hello from Client";
    char response[1024];
    struct sockaddr_in server_addr;
    socklen_t len= sizeof(server_addr);

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);

    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,len);
    recvfrom(sockfd,response,sizeof(response),0,(struct sockaddr*)&server_addr,&len);
    printf("Message from server: %s",response);
    close(sockfd);
}