#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROBABLITY 20

int totalFrames, windowSize, totaltransmissions=0, base=0;

void transmission(){
    while(base<totalFrames){
        for(int i=base;i<base+windowSize &&i<totalFrames;i++){
            printf("sending frame %d..\n",i+1);
            totaltransmissions++;
        }
        int ackAll=1;
        for(int i=base;i<base+windowSize &&i<totalFrames;i++){
            int rand_val= rand()%100;
            if(rand_val<PROBABLITY){
                printf("ack for frame %d lost!!\n",i+1);
                printf("GoBackN: retransmitting frames from %d..\n",i+1);
                ackAll=0;
                break;
            }
            else{
                printf("ack for frame %d success\n",i+1);

            }

        }
        printf("\n");
        if(ackAll){
            base+=windowSize;
        }
    
    }
}
void main(){
    srand(time(0));
    printf("enter total frmaes and window size\n");
    scanf("%d %d",&totalFrames,&windowSize);
    transmission();
    printf("Total transmission.%d.\n",totaltransmissions);
}