#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define LOSS_PROBABLITY 20
#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

int send_frame(int frame_num){
    printf("sending frame %d\n",frame_num);
    sleep(1);
    int rand_value= rand()%100;
    if(rand_value<LOSS_PROBABLITY){
        printf("frame %d lost during transmission\n",frame_num);
        return 0;
    }
    else{
        printf("frame %d sent successfully\n",frame_num);
        return 1;
    }
}
int receive_ack(int frame_num){
    printf("sending ack for frame %d\n",frame_num);
    sleep(1);
    int rand_value= rand()%100;
    if(rand_value<LOSS_PROBABLITY){
        printf("ack for frame %d lost during transmission\n",frame_num);
        return 0;
    }
    else{
        printf("ack for frame %d sent successfully\n",frame_num);
        return 1;
    }
}

void selective_repeat_arq(){
    int sent_frames[TOTAL_FRAMES]={0};
    int ack_received[TOTAL_FRAMES]={0};
    int base=0;
    while(base<TOTAL_FRAMES){
    for(int i=base;i<base+WINDOW_SIZE &&i<TOTAL_FRAMES;i++){
        if(!sent_frames[i]){
            sent_frames[i]=send_frame(i);
        }
    }
    for(int i=base;i<base+WINDOW_SIZE &&i<TOTAL_FRAMES;i++){
        if(sent_frames[i] && (!ack_received[i])){
            ack_received[i]=receive_ack(i);
        }
    }
    while(base<TOTAL_FRAMES && ack_received[base]){
        printf("sliding window forward...");
        base++;
    }
}
}

void main(){
    srand(time(0));
    selective_repeat_arq();
}