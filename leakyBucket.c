#include <stdio.h>


void leaky_bucket(int bucket_capacity, int leak_rate, int num, int packets[]){
    int bucket=0;
    printf("Time\tIncoming\tBucket\tLeaked\tRemainig\n");
    for(int i=0;i<num;i++){
        printf("%d\t%d\t",i+1,packets[i]);
        bucket+=packets[i];
        if(bucket>bucket_capacity){
            printf("%d Overflow, dropped %d\t",bucket,bucket-bucket_capacity);
            bucket=bucket_capacity;
        }else{
            printf("%d\t",bucket);
        }
        int leaked= bucket>=leak_rate?leak_rate:bucket;
        printf("%d\t%d\n",leaked,bucket-leaked);
        bucket=bucket-leaked;
        
    }
    int time=num+1;
    while(bucket>0){
        int leaked=bucket>=leaked?leak_rate:bucket;
        printf("%d\t%d\t%d\t%d\t%d\n",time,0,bucket,leaked, bucket-leaked);
        bucket-=leaked;
        time++;
    }
}

void main(){
    int bucket_capacity, leak_rate, num;
    printf("enter bucket capacity, leak rate, num of packets\n");
    scanf("%d %d %d",&bucket_capacity,&leak_rate,&num);
    int packets[num];
    printf("enter the packet sizes\n");
    for(int i=0;i<num;i++){
        scanf("%d",&packets[i]);
    }
    leaky_bucket(bucket_capacity,leak_rate,num, packets);
}