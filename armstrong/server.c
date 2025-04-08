#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#include <stdlib.h>


int check_armstrong(int num){
    int original= num, r, result=0,n=0;
    int temp=num;
    while(temp>0){
        temp/=10;
        n++;
    }
    temp=num;
    while(temp>0){
        r=temp%10;
        result+= pow(r,n);
        temp/=10;
    }
    if(original==result){
        return 1;
    }
    else{
        return 0;
    }
}

void main(){
    int sockfd,newsock;
    struct sockaddr_in client_addr,server_addr;
    char buffer[1024]={0};
    char response[1024]={0};
    socklen_t len= sizeof(client_addr);

    sockfd=socket(AF_INET, SOCK_STREAM,0);
    server_addr.sin_addr.s_addr =INADDR_ANY;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    
    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("bind failed\n");
        exit(0);
    }
    listen(sockfd,1);
    printf("server waiting for connection\n");
    newsock=accept(sockfd,(struct sockaddr*)&client_addr,&len);
    printf("client connected\n");
    while(1){
        read(newsock,buffer,sizeof(buffer));
        if(strncmp(buffer,"exit",4)==0){
            printf("exiting..\n");
            break;
        }
        int num =atoi(buffer);

        if(check_armstrong(num)){
            strcpy(response,"is armstrong\n");
        }
        else{
            strcpy(response,"is not armsrong\n");
        }
        send(newsock,response,strlen(response),0);
    }
    close(sockfd);
    close(newsock);
}