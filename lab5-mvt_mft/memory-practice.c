#include<stdio.h>

#define MAX_PARTITIONS 100

typedef struct {
    int size;
    int allocated;
    int internal_fragmentation;
} Partition;

void mft(int process_sizes[],int num_processes,Partition partitions[],int num_partitions,int leftover){
    int total_internal_fragmentation=0;
    int total_external_fragmentation=0;

    for(int i=0;i<num_processes;i++){
        int allocated=0;

        for(int j=0;j<num_partitions;j++){
            if(partitions[j].allocated==0 && partitions[j].size>=process_sizes[i]){
                partitions[j].allocated=1;
                allocated=1;
                partitions[j].internal_fragmentation = partitions[j].size - process_sizes[i];
                total_internal_fragmentation += partitions[j].internal_fragmentation;
                printf("Process with size %d was allocated to partition %d\n",process_sizes[i],j);
                break;
            }
        }

        if(allocated==0){
            printf("process %d was not allocated\n",i);
        }
    }

    for(int i=0;i<num_partitions;i++){
        if(partitions[i].allocated==0){
            total_external_fragmentation+=partitions[i].size;
        }
    }
    total_external_fragmentation+=leftover;

    printf("total internal fragmentation=%d\ntotal external fragmentation=%d\n",total_internal_fragmentation,total_external_fragmentation);
}


int main(){
    int mem_size;
    printf("Enter the size of the memory: ");
    scanf("%d",&mem_size);
    
    int partition_size;
    printf("Enter the size of each partition: ");
    scanf("%d",&partition_size);

    int num_partitions = mem_size/partition_size;
    int leftover = mem_size - partition_size*num_partitions;
    Partition partitions[num_partitions];

    for(int i=0;i<num_partitions;i++){
        partitions[i].size=partition_size;
        partitions[i].allocated=0;
        partitions[i].internal_fragmentation=partition_size;
    }

    int num_processes;
    printf("Enter the no of processes: ");
    scanf("%d",&num_processes);

    int process_sizes[num_processes];
    for(int i=0;i<num_processes;i++){
        printf("Enter the size of process %d: ",i);
        scanf("%d",&process_sizes[i]);
    }

    mft(process_sizes,num_processes,partitions,num_partitions,leftover);

    return 0;
}