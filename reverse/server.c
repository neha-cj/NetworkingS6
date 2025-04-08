//tcp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void reverse(char *str){
    int i,j;
    char temp;
    i=0;
    j=strlen(str)-1;
    while(i<j){
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }
}

void main(){
    int sockfd,newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024]={0};

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    listen(sockfd,3);
    newsock=accept(sockfd,(struct sockaddr*)&client,&len);
    printf("server connceted to client\n");

    while(1){
        memset(buffer,0,sizeof(buffer));
        read(newsock, buffer, sizeof(buffer));
        printf("%s\n",buffer);
        reverse(buffer);
        send(newsock, buffer, strlen(buffer),0);

    }
    close(sockfd);
    close(newsock);

}