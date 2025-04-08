#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void fibonnaci(int num, char*result){
    result[0] = '\0';
    int a=0,b=1,c;
    char buffer[20];
    sprintf(buffer,"%d",a);
    if(num>0){
        sprintf(buffer,"%d",b);
        strcat(result,buffer);
    }
    for(int i=2;i<num;i++){
        c=a+b;
        a=b;
        b=c;
        sprintf(buffer," %d",c);
        strcat(result,buffer);
    }
}

void main(){
    int sockfd;
    struct sockaddr_in server,client;
    char buffer[1024]={0};
    socklen_t len = sizeof(client);

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("udp server is running..\n");
    while(1){
        memset(buffer,0,sizeof(buffer));
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&client,&len);
        printf("receiver: %s",buffer);
        int num = atoi(buffer);
        fibonnaci(num,buffer);
        sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&client,len);
        
    }
    close(sockfd);

}